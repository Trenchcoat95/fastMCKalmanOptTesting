/*
    gSystem->AddIncludePath("-I\"$fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/\"")
      gSystem->Load("$fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/AliExternalTrackParam.so");
   .L $fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.cxx+g
    .L $fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulationTest.C+g
    AliPDG::AddParticlesToPdgDataBase();
    testTPCmuons(10000,kTRUE);
    testTPC(10000,kTRUE);            //setup for the looper development
    testAlice(10000,kTRUE);          // ALICE setup
    testAlice3Werner(50000,kTRUE)    // ALICE3 setup
    //initTreeFast()
    .> a.log
     testPCStream(5000,kTRUE);
     .>

 */
#include "fastSimulation.h"
#include "TTreeStream.h"
#include "TStopwatch.h"
#include "TRandom.h"
#include "TChain.h"
#include "AliXRDPROOFtoolkit.h"
//#include "AliDrawStyle.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TPad.h"
#include "TCanvas.h"
#include "AliPID.h"
#include <iostream>
#include <string>
#include <fstream>
const Float_t kDecayFraction=0.5;
const Float_t kRandomPDGFraction=0.5;

TChain * treeFast = 0;
TChain * treeTurn=0;
TChain * treeUnit0=0;
TChain * treeSeed=0;
void testDummy(){
  double r[]={0,0,0};
  double p[]={1,0,0};
  //particle.simulateParticle(geom, r,p,211,200,90);
}

/// test for looper development with continous tracking - ALICE TPC gas cylinder without ITS - emulation of the gas detectors
/// \param nParticles
/// \param dumpStream
void testTPC(Int_t nParticles, bool dumpStream=1){

  const Int_t   nLayerTPC=250;
  const Float_t kMinPt=0.02;
  const Float_t kMax1Pt=1./100.;
  const Float_t kFlatPtMax=50;
  const Float_t kFlatPtFraction=0.3;
  const Float_t smearR=200;
  const Float_t smearZ=200;
  const Float_t  xx0=7.8350968e-05;
  const Float_t  xrho=0.0016265266;
  const Float_t kNominalFraction=0.3;     // fraction of nominal properties
  const Float_t kMaterialScaling=10;      // material random scaling to
  const Float_t kMaxResol=0.2;            // point resolution scan max resolution
  const Float_t kMinResol=0.01;           //  point resolution scan min resolution
  const Float_t kDefResol=0.1;           //  point resolution scan min resolution

  TStopwatch timer;
  timer.Start();
  fastGeometry geom(nLayerTPC+1);
  geom.fBz=5;


  float resol[2]={0.000001,0.000001};
  resol[0]=0.000001;
  resol[1]=0.000001;
  geom.setLayerRadiusPower(0,nLayerTPC,1,nLayerTPC,1.0,xx0,xrho,resol);

  TTreeSRedirector *pcstream = new TTreeSRedirector("fastParticleMS.root","recreate");
  TTree * tree = 0;
  for (Int_t i=0; i<nParticles; i++){
    fastParticle particle(nLayerTPC+1);
    particle.fAddMSsmearing=true;
    particle.fgStreamer=pcstream;
    particle.gid=i;
    // generate scan detector properties
    Float_t matScaling  =(gRandom->Rndm()<kNominalFraction) ? 1.:  (gRandom->Rndm()*kMaterialScaling)+1;
    Float_t resolScan=(gRandom->Rndm()<kNominalFraction) ? kDefResol: gRandom->Rndm()*kMaxResol;
    for (Int_t iLayer=0; iLayer<geom.fLayerX0.size();iLayer++) {
      geom.fLayerX0[iLayer] = xx0 * matScaling;
      geom.fLayerRho[iLayer] = xrho * matScaling;
      geom.fLayerResolRPhi[iLayer] = resolScan;
      geom.fLayerResolZ[iLayer] = resolScan;
    }
    double r[]     = {0,0,0};
    Bool_t  isSecondary=gRandom->Rndm()<0.5;
    // isSecondary=kFALSE;
    if (isSecondary){
        r[0]=2*(gRandom->Rndm()-0.5)*smearR;
        r[1]=2*(gRandom->Rndm()-0.5)*smearR;
        r[2]=2*(gRandom->Rndm()-0.5)*smearZ;
    }
    double pt      = kMinPt/(kMax1Pt*kMinPt+gRandom->Rndm());
    if (gRandom->Rndm()<kFlatPtFraction) pt= gRandom->Rndm()*kFlatPtMax;
    double phi     = gRandom->Rndm()*TMath::TwoPi();
    double theta = (gRandom->Rndm()-0.5)*3;
    double p[]={pt*sin(phi),pt*cos(phi),pt*theta};
    int    pidCode=int(gRandom->Rndm()*8);
    long  charge  = (gRandom->Rndm()<0.5) ? -1:1;
    long   pdgCode = AliPID::ParticleCode(pidCode)*charge;
    if (gRandom->Rndm()<kRandomPDGFraction) pdgCode=0;
    Bool_t  hasDecay=(gRandom->Rndm()<kDecayFraction);
    Float_t decayLength= hasDecay ?gRandom->Rndm()*geom.fLayerRadius[geom.fLayerRadius.size()-1]:0;
    particle.fDecayLength=decayLength;
    particle.simulateParticle(geom, r,p,pdgCode, 250,nLayerTPC);
    particle.reconstructParticle(geom,pdgCode,nLayerTPC);
    particle.reconstructParticleRotate0(geom,pdgCode,nLayerTPC);
    //particle.simulateParticle(geom, r,p,211, 250,161);
    //particle.reconstructParticle(geom,211,160);
    if (dumpStream==kFALSE) continue;
    if (tree) tree->Fill();
    else {
      (*pcstream) << "fastPart" <<
                  "i=" << i <<
                  "geom.="<<&geom<<
                  "hasDecay="<<hasDecay<<
                  "isSecondary="<<isSecondary<<
                  "pidCode="<<pidCode<<
                  "pdgCode="<<pdgCode<<
                  "charge="<<charge<<
                  "part.=" << &particle <<
                  "\n";
      tree=  ((*pcstream) << "fastPart").GetTree();
    }
  }
  delete pcstream;
  timer.Print();
}

/// testAlice configuration ITS+TPC with material budget as in the Run1/2
/// \param nParticles
/// \param dumpStream
void testAlice(Int_t nParticles, bool dumpStream){
  const Float_t smearR=10;
  const Float_t smearZ=10;
  const Float_t resolY=0.1;
  const Float_t resolZ=0.1;
  const Float_t bz=5;
  const Int_t   nLayerTPC=160;
  const Float_t kMinPt=0.02;
  const Float_t kMax1Pt=1./100.;
  //const Float_t kMax1Pt=1./0.1;
  const Float_t kThetaMax=2.;
  const Float_t kMaxLength=300;
  // values as obtaied from the gromManager see -  https://alice.its.cern.ch/jira/browse/PWGPP-613?focusedCommentId=263181&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-263181
  const Float_t  xx0=7.8350968e-05;
  const Float_t xrho=0.0016265266;
  //
  TStopwatch timer;
  timer.Start();
  fastGeometry geom= fastGeometry(nLayerTPC);
  geom.fBz=bz;
  fastParticle particle=fastParticle(nLayerTPC);
  // ITS emulation  0 6 layers wit  O(0.001 cm) resolution
  //     X0 is radiation length per layer and rho is the integrated density per layer - obtained from Geant simulation
  float resol[2]={0.001,0.001};
  geom.setLayerRadiusPower(0,5, 4,37, 1.0,0.006,0.16, resol);
  // TPC emulation
  //    X0 is radiation length per layer and rho is the integrated density per layer - obtained from Geant simulation
  resol[0]=0.1;
  resol[1]=0.1;
  //geom.setLayerRadiusPower(6,nLayerTPC,89,260,1.0,0.000025,0.0009,resol);
  geom.setLayerRadiusPower(6,nLayerTPC,89,260,1.0,xx0,xrho,resol);
  //
  TTreeSRedirector *pcstream = new TTreeSRedirector("fastParticleALICE.root","recreate");
  particle.fgStreamer=pcstream;
  TTree * tree = 0;
  for (Int_t i=0; i<nParticles; i++){
    double r[]     = {0,0,0};
    Bool_t  isSecondary=gRandom->Rndm()<0.5;
    isSecondary=kFALSE;
    if (isSecondary){
        r[0]=2*(gRandom->Rndm()-0.5)*smearR;
        r[1]=2*(gRandom->Rndm()-0.5)*smearR;
        r[2]=2*(gRandom->Rndm()-0.5)*smearZ;
    }
    double pt      = kMinPt/(kMax1Pt*kMinPt+gRandom->Rndm());
    double phi     = gRandom->Rndm()*TMath::TwoPi();
    double theta = 2.*(gRandom->Rndm()-0.5)*kThetaMax;
    double p[]={pt*sin(phi),pt*cos(phi),pt*theta};
    int    pidCode=int(gRandom->Rndm()*8);                   // PID code of particles - 0-electron ,1-muon, 2-pion, 3-Kaon

    //pidCode=2;
    long  charge  = (gRandom->Rndm()<0.5) ? -1:1;
    long    pdgCode = AliPID::ParticleCode(pidCode)*charge;  // PID code covnerted to the PdgCode
    if (gRandom->Rndm()<kRandomPDGFraction) pdgCode=0;
     Float_t decayLength= (gRandom->Rndm()<kDecayFraction) ?gRandom->Rndm()*geom.fLayerRadius[geom.fLayerRadius.size()-1]:0;
    particle.fDecayLength=decayLength;
    particle.simulateParticle(geom, r,p,pdgCode, kMaxLength,nLayerTPC);
    particle.reconstructParticle(geom,pdgCode,nLayerTPC);
    particle.reconstructParticleRotate0(geom,pdgCode,nLayerTPC);

    if (dumpStream==kFALSE) continue;
    if (tree) tree->Fill();
    else {
      (*pcstream) << "fastPart" <<
                  "i=" << i <<
                  "isSecondary="<<isSecondary<<
                  "pidCode="<<pidCode<<
                  "pdgCode="<<pdgCode<<
                  "charge="<<charge<<
                  "part.=" << &particle <<
                  "\n";
      tree=  ((*pcstream) << "fastPart").GetTree();
    }
  }
  delete pcstream;
  timer.Print();
}


/// testAlice 3 configuration as proposed in https://github.com/preghenella/DelphesO2/blob/a058f94f6cb887edcf725fd991d16ca5f7b76e0b/src/lutWrite.werner.cc
/// \param nParticles
/// \param dumpStream
void testAlice3Werner(Int_t nParticles, bool dumpStream){
  // simulation setup parameters
  const Float_t smearR=10;
  const Float_t smearZ=10;

  const Float_t kMinPt=0.02;
  const Float_t kMax1Pt=1./100.;
  //const Float_t kMax1Pt=1./0.1;
  const Float_t kThetaMax=2.;
  const Float_t kMaxLength=300;
  //
  // new ideal Pixel properties?
  const Float_t x0IB     = 0.001;
  const Float_t x0OB     = 0.01;
  const Float_t xrhoIB     = 2.3292e-02; // 100 mum Si
  const Float_t xrhoOB     = 2.3292e-01; // 1000 mum Si
  const Float_t resRPhiIB     = 0.00025;
  const Float_t resZIB        = 0.00025;
  const Float_t resRPhiOB     = 0.00100;
  const Float_t resZOB        = 0.00100;
  const Float_t eff           = 0.98;
  //
  const Float_t bpipe0R       = 0.48;
  const Float_t x0bpipe0      = 0.00042;
  const Float_t xrhobpipe0    = 2.772e-02; // 150 mum Be
  const Float_t bpipe1R       = 3.7 ;
  const Float_t x0bpipe1      = 0.0014;
  const Float_t xrhobpipe1    = 9.24e-02; // 500 mum Be
  const Float_t xOuter        = 100.;
  const Int_t nLayersFull=30;
  //
  Float_t resolNo[2]={0,0};
  Float_t resolIB[2]={resRPhiIB,resRPhiIB};
  Float_t resolOB[2]={resRPhiOB,resRPhiOB};
  //
  // parameters
  float bz=0.5;
  Double_t scaleR=1;
  Int_t    nLayersIB=3;
  Float_t  powerIB=1;
  Int_t    nLayersOB=10;
  Float_t  powerOB=1.0;
  Int_t nLayersAll=2+(nLayersIB+nLayersOB);

  //
  TStopwatch timer;
  timer.Start();
  TTreeSRedirector *pcstream = new TTreeSRedirector("fastParticle.root","recreate");
  TTree * tree = 0;
  fastGeometry geom= fastGeometry(nLayersAll);
  geom.fBz=bz;
  fastParticle particle=fastParticle(2*nLayersAll);
  particle.fgStreamer=pcstream;
  //
  geom.setLayer(0,bpipe0R*scaleR, x0bpipe0,xrhobpipe0 , resolNo);
  geom.setLayerRadiusPower(1, nLayersIB+1,bpipe0R*1.02*scaleR, bpipe1R*0.98*scaleR, powerIB,x0IB,xrhoIB, resolIB);
  geom.setLayer(nLayersIB+1, bpipe1R*scaleR, x0bpipe1,xrhobpipe1 , resolNo);
  geom.setLayerRadiusPower(nLayersIB+2, nLayersIB+2+nLayersOB, bpipe1R*1.02*scaleR, xOuter *scaleR, 1, x0OB,xrhoOB , resolOB);
  //

  //geom.setLayerRadiusPower();

  //

  for (Int_t i=0; i<nParticles; i++){
    double r[]     = {0+gRandom->Rndm()*0.000000001,gRandom->Rndm()*0.000000001,0};
    Bool_t  isSecondary=gRandom->Rndm()<0.5;
    isSecondary=kFALSE;
    if (isSecondary){
        r[0]=2*(gRandom->Rndm()-0.5)*smearR;
        r[1]=2*(gRandom->Rndm()-0.5)*smearR;
        r[2]=2*(gRandom->Rndm()-0.5)*smearZ;
    }
    double pt      = kMinPt/(kMax1Pt*kMinPt+gRandom->Rndm());
    double phi     = gRandom->Rndm()*TMath::TwoPi();
    double theta = 2.*(gRandom->Rndm()-0.5)*kThetaMax;
    double p[]={pt*sin(phi),pt*cos(phi),pt*theta};
    int    pidCode=int(gRandom->Rndm()*8);                   // PID code of particles - 0-electron ,1-muon, 2-pion, 3-Kaon
    long  charge  = (gRandom->Rndm()<0.5) ? -1:1;
    long    pdgCode = AliPID::ParticleCode(pidCode)*charge;  // PID code covnerted to the PdgCode
    if (gRandom->Rndm()<kRandomPDGFraction) pdgCode=0;
     Float_t decayLength= (gRandom->Rndm()<kDecayFraction) ?gRandom->Rndm()*geom.fLayerRadius[geom.fLayerRadius.size()-1]:0;
    particle.fDecayLength=decayLength;
    particle.simulateParticle(geom, r,p,pdgCode, kMaxLength,nLayersAll*2);
    particle.reconstructParticle(geom,pdgCode,nLayersAll*2);
    particle.reconstructParticleRotate0(geom,pdgCode,nLayersAll*2);

    if (dumpStream==kFALSE) continue;
    if (tree) tree->Fill();
    else {
      (*pcstream) << "fastPart" <<
                  "i=" << i <<
                  "isSecondary="<<isSecondary<<
                  "pidCode="<<pidCode<<
                  "pdgCode="<<pdgCode<<
                  "charge="<<charge<<
                  "part.=" << &particle <<
                  "\n";
      tree=  ((*pcstream) << "fastPart").GetTree();
    }
  }
  delete pcstream;
  timer.Print();
}


void setAliases(TTree & tree){
  fastParticle::setAliases(tree);
//  tree.SetAlias("gxIn","cos(part.fParamIn[].fAlpha)*part.fParamIn[].fX");
//  tree.SetAlias("gyIn","sin(part.fParamIn[].fAlpha)*part.fParamIn[].fX");
//  tree.SetAlias("gxMC","cos(part.fParamMC[].fAlpha)*part.fParamMC[].fX");
//  tree.SetAlias("gyMC","sin(part.fParamMC[].fAlpha)*part.fParamMC[].fX");
//  tree.SetAlias("gzMC","part.fParamMC[].fP[1]");
//  tree.SetAlias("rMC","part.fParamMC[].fX");
//  tree.SetAlias("ptMC","part.fParamMC[0].fData.Pt()");
//  tree.SetAlias("pMC","part.fParamMC[0].fData.P()");
//  tree.SetAlias("ptRec","part.fParamIn[0].fData.Pt()");
//  //
//  tree.SetAlias("layer","Iteration$");
//  tree.SetAlias("c0MC","sqrt(part.fParamMC[].fC[0])");
//  tree.SetAlias("c2MC","sqrt(part.fParamMC[].fC[2])");
//  tree.SetAlias("c14MC","sqrt(part.fParamMC[].fC[14])");
//  tree.SetAlias("c0In","sqrt(part.fParamIn[].fC[0])");
//  tree.SetAlias("c2In","sqrt(part.fParamIn[].fC[2])");
//  tree.SetAlias("c0InRot","sqrt(part.fParamInRot[].fC[0])");
//  tree.SetAlias("c2InRot","sqrt(part.fParamInRot[].fC[2])");
//  tree.SetAlias("dEdxExp","AliExternalTrackParam::BetheBlochAleph(pMC/AliPID::ParticleMass(pidCode))");
//  tree.SetAlias("dEdxExpSolid","AliExternalTrackParam::BetheBlochSolid(pMC/AliPID::ParticleMass(pidCode))");
//  tree.SetAlias("dEdxExpSolidL","AliExternalTrackParam::BetheBlochSolid(part.fParamMC[].fData.P()/AliPID::ParticleMass(pidCode))");
//  tree.SetAlias("dEdxExpSolidL1","AliExternalTrackParam::BetheBlochSolid(part.fParamMC[Iteration$-1].fData.P()/AliPID::ParticleMass(pidCode))");
//  tree.SetAlias("elossTPCIn","(part.fParamIn[159].fData.GetP()-part.fParamIn[7].fData.GetP())/part.fParamMC[1].fData.GetP()");
//  tree.SetAlias("elossTPCMC","(part.fParamMC[159].fData.GetP()-part.fParamMC[7].fData.GetP())/part.fParamMC[1].fData.GetP()");
}

void initTreeFast(const char * inputList="fastParticle.list"){
  const char* inputListPath=gSystem->ExpandPathName(inputList);
  treeFast  = AliXRDPROOFtoolkit::MakeChainRandom(inputListPath,"fastPart",0,10000);
  treeTurn  = AliXRDPROOFtoolkit::MakeChainRandom(inputListPath,"turn",0,10000);
  treeUnit0  = AliXRDPROOFtoolkit::MakeChainRandom(inputListPath,"UnitTestDumpCorrectForMaterial",0,10000);
  treeSeed  = AliXRDPROOFtoolkit::MakeChainRandom(inputListPath,"seedDump",0,10000);
  treeFast->SetMarkerStyle(21);
  treeFast->SetMarkerSize(0.5);
   treeUnit0->SetMarkerStyle(21);
  treeUnit0->SetMarkerSize(0.5);
  treeSeed->BuildIndex("gid");
  treeFast->BuildIndex("gid");
  treeSeed->AddFriend(treeFast,"F");

  //AliDrawStyle::SetDefaults();
  //AliDrawStyle::ApplyStyle("figTemplate");
  gStyle->SetOptTitle(1);
  setAliases(*treeFast);
  //
  treeUnit0->SetAlias("dEdxOutIn","AliExternalTrackParam::BetheBlochSolid(0+paramStepRK.P()/mass)/AliExternalTrackParam::BetheBlochSolid(paramIn.P()/mass)");
  treeUnit0->SetAlias("dEdxIn","AliExternalTrackParam::BetheBlochSolid(paramIn.P()/mass+0)");
  treeUnit0->SetAlias("dEdxOut","AliExternalTrackParam::BetheBlochSolid(paramRK.P()/mass+0)");

}

void drawDisplay(){
  TCanvas * canvas1 = new TCanvas("c1","c1",600,500);
  gSystem->mkdir("fig/");
  treeFast->Draw("gyMC:gxMC:part.fParamMC[0].fP[4]","","colz",100);
  gPad->SaveAs("fig/gygzMC.png");
  treeFast->Draw("gyIn:gxIn:part.fParamMC[0].fP[4]","","colz",100);
  gPad->SaveAs("fig/gygzIn.png");
}


/*

void testDataFrame(){
  RDataFrame d(100); // a RDF that will generate 100 entries (currently empty)
  int x = -1;
  auto d_with_columns = d.Define("x", [&x] { return ++x; })
                       .Define("xx", [&x] { return x*x; });
  d_with_columns.Snapshot("myNewTree", "newfile.root");
  //
  RDataFrame df("particles", "particle.root");
  //auto zMean = d.Define("z", "sqrt(x*x + y*y)").Mean("z");
}

*/

/*

void checkMaterialAliRoot(){
  Double_t x0[3]={0,0,0};
  Double_t x1[3]={6,0,0};
  Double_t param[10];
  AliTrackerBase::MeanMaterialBudget(x0,x1,param);
  Double_t xrho=param[0]*param[4], xx0=param[1];
  // root [34] xrho
  // (Double_t)4.66295523219595331e-01
  // root [35] xx0
  // (Double_t)1.32765905087294800e-02

}*/

void testTPCmuons(Int_t nParticles, bool dumpStream=1, float resol0=0.1, float resol1=0.1, float kPtfixed = 1.5,
                                                       bool kAddEloss=true, bool kAddMSsmearing=true, 
                                                       bool kAddElossHelix=true, bool kAddMSHelix=true,
                                                       bool kAddElossKalman=true, bool kAddMSKalman=true){

  const Int_t   nLayerTPC=250;
  //const Float_t kPtfixed = 1.5;
  const Float_t rangeR=200;
  const Float_t rangeZ=200;
  const Float_t xx0=7.8350968e-05;
  const Float_t xrho=0.0016265266;
  const Float_t kMaterialScaling=10;      ////Promote to global variable
            


  TStopwatch timer;
  timer.Start();
  fastGeometry geom(nLayerTPC+1);
  geom.fBz=5;


  float resol[2]={0.0001,0.0001};
  resol[0]=resol0;                   /////sets the smearing as well as the resolution, set to 0 if you don't want smearing
  resol[1]=resol1;
  geom.setLayerRadiusPower(0,nLayerTPC,1,nLayerTPC,1.0,xx0,xrho,resol);

  //std::string filename = "MC_01smear_noEloss_noMS_Seed_Eloss_MS_Kalman_noEloss_noMS";

  std::string smear = std::to_string(resol0);
  smear.erase(remove(smear.begin(), smear.end(), '.'), smear.end());
  smear.erase ( smear.find_last_not_of('0') + 1, std::string::npos );
  std::string pTstr = std::to_string(kPtfixed);
  //pTstr.erase(remove(pTstr.find('.'), pTstr.end(), '0'), pTstr.end());
  pTstr.erase ( pTstr.find('0') + 1, std::string::npos );
  pTstr.erase(remove(pTstr.begin(), pTstr.end(), '.'), pTstr.end());
  
  std::string MC_Eloss = kAddEloss? "Eloss":"noEloss";
  std::string MC_MS = kAddMSsmearing? "MS":"noMS";
  std::string Seed_Eloss = kAddElossHelix? "Eloss":"noEloss";
  std::string Seed_MS = kAddMSHelix? "MS":"noMS";
  std::string Kalman_Eloss = kAddElossKalman? "Eloss":"noEloss";
  std::string Kalman_MS = kAddMSKalman? "MS":"noMS";

  std::string filename = "MC_"+smear+"smear_"+MC_Eloss+"_"+MC_MS+"_Seed_"+Seed_Eloss+"_"+Seed_MS+"_Kalman_"+Kalman_Eloss+"_"+Kalman_MS;
  std::string path ="/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/data/testTPCmuons/fixedpt"+pTstr+"/";
  
  //std::string filename = "MC_01smear_noEloss_noMS_Seed_noEloss_noMS_Kalman_noEloss_noMS";
  //std::string path ="/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalman/data/testTPCmuons/fixedpt15/";
  std::string dirname = path+filename;
  std::string totalname = dirname +"/"+filename+".root";
  std::string filelist = dirname + "/fastParticle.list";
  const char* cdir = const_cast<char*>(dirname.c_str());
  const char* ctotal = const_cast<char*>(totalname.c_str());

  std::cout<< "Filename: "<<totalname<<std::endl;


  gSystem->mkdir(cdir,1);

  std::ofstream fw(filelist, std::ofstream::out);
  fw << totalname ;
  fw.close();
  
  
  TTreeSRedirector *pcstream = new TTreeSRedirector(ctotal,"recreate");
  TTree * tree = 0;
  int counter = 0;
  for (Int_t i=0; i<nParticles; i++){
    fastParticle particle(nLayerTPC+1);


    ////Parameters that regulate the simulation
    //const Float_t kResol=0.01;      
    particle.fAddEloss=kAddEloss;
    particle.fAddMSsmearing=kAddMSsmearing;
    particle.fAddElossGausssmearing=false;
    particle.fAddElossLandausmearing=false;

    ////Parameters that regulate the seeding
    particle.fAddElossHelix=kAddElossHelix;
    particle.fAddMSHelix=kAddMSHelix;

    ////Parameters that regulate the Kalman Filter Reconstruction
    particle.fAddElossKalman=kAddElossKalman;
    particle.fAddMSKalman=kAddMSKalman;
    



    particle.fgStreamer=pcstream;
    particle.gid=i;
    // generate scan detector properties
    for (Int_t iLayer=0; iLayer<geom.fLayerX0.size();iLayer++) {
      geom.fLayerX0[iLayer] = xx0 * kMaterialScaling;
      geom.fLayerRho[iLayer] = xrho * kMaterialScaling;
      geom.fLayerResolRPhi[iLayer] =resol[0];
      geom.fLayerResolZ[iLayer] = resol[1];
    }
    double r[]     = {0,0,0};
    Bool_t  isSecondary=1;
    // isSecondary=kFALSE;
    if (isSecondary){
        r[0]=2*(gRandom->Rndm()-0.5)*rangeR;
        r[1]=2*(gRandom->Rndm()-0.5)*rangeR;
        r[2]=2*(gRandom->Rndm()-0.5)*rangeZ;
    }

    ////testfixedpos
    //r[0]=-200;
    //r[1]=0;
    //r[2]=0;

    //double pt      = kMinPt/(kMax1Pt*kMinPt+gRandom->Rndm());             //randomize Initiat pt
    //if (gRandom->Rndm()<kFlatPtFraction) pt= gRandom->Rndm()*kFlatPtMax;
    double pt = kPtfixed;
    double phi     = gRandom->Rndm()*TMath::TwoPi();
    double theta = (gRandom->Rndm()-0.5)*3;

    /// test limited range of angles
    //phi     = (gRandom->Rndm()-0.5)*TMath::TwoPi()*20/360;
    //theta   = (gRandom->Rndm()-0.5)*TMath::TwoPi()*5/360;
    
    double p[]={pt*sin(phi),pt*cos(phi),pt*theta};
    //int    pidCode=int(gRandom->Rndm()*8);                                //randomize PIDCode
    int    pidCode= 1;
    long   charge  = (gRandom->Rndm()<0.5) ? -1:1;
    long   pdgCode = AliPID::ParticleCode(pidCode)*charge;
    //if (gRandom->Rndm()<kRandomPDGFraction) pdgCode=0;
    //Bool_t  hasDecay=(gRandom->Rndm()<kDecayFraction);
    //Float_t decayLength= hasDecay ?gRandom->Rndm()*geom.fLayerRadius[geom.fLayerRadius.size()-1]:0;
    particle.fDecayLength=0;                                                //don't decay particles

    float recostatus = 0;
    particle.simulateParticleOptions(geom, r,p,pdgCode, 250,nLayerTPC);
    recostatus = particle.reconstructParticleOptions(geom,pdgCode,nLayerTPC);
    if (recostatus<0) counter++;

    //particle.reconstructParticleRotate0(geom,pdgCode,nLayerTPC);
    //particle.simulateParticle(geom, r,p,211, 250,161);
    //particle.reconstructParticle(geom,211,160);
    if (dumpStream==kFALSE) continue;
    if (tree) tree->Fill();
    else {
      (*pcstream) << "fastPart" <<
                  "i=" << i <<
                  "geom.="<<&geom<<
                  "isSecondary="<<isSecondary<<
                  "pidCode="<<pidCode<<
                  "pdgCode="<<pdgCode<<
                  "charge="<<charge<<
                  "part.=" << &particle <<
                  "\n";
      tree=  ((*pcstream) << "fastPart").GetTree();
    }
  }
  delete pcstream;
  std::cout<<"Failed recos: "<<counter<<std::endl;
  timer.Print();
}


void testTPCVSgarlite(Int_t nParticles, bool dumpStream=1, float resol0=0.1, float resol1=0.1,
                                        bool kAddEloss=true, bool kAddMSsmearing=true, 
                                        bool kAddElossHelix=true, bool kAddMSHelix=true,
                                        bool kAddElossKalman=true, bool kAddMSKalman=true){

  const Int_t   nLayerTPC=277;
  const Int_t   nPoints=nLayerTPC*3;
  //const Float_t kPtfixed = 1.5;
  const Float_t rangeR=200;
  const Float_t rangeZ=200;
  const Float_t xx0=7.8350968e-05;
  const Float_t xrho=0.0016265266;
  const Float_t kMaterialScaling=10;      ////Promote to global variable
  double GArCenter[3]={0,-150.473,1486}; 
  double GAr_r = 349.9;
  double GAr_L = 669.6;
            


  TStopwatch timer;
  timer.Start();
  fastGeometry geom(nLayerTPC+1);
  geom.fBz=5;


  float resol[2]={0.0001,0.0001};
  resol[0]=resol0;                   /////sets the smearing as well as the resolution, set to 0 if you don't want smearing
  resol[1]=resol1;
  geom.setLayerRadiusPower(0,nLayerTPC,1,nLayerTPC,1.0,xx0,xrho,resol);

  //std::string filename = "MC_01smear_noEloss_noMS_Seed_Eloss_MS_Kalman_noEloss_noMS";

  std::string smear = std::to_string(resol0);
  smear.erase(remove(smear.begin(), smear.end(), '.'), smear.end());
  smear.erase ( smear.find_last_not_of('0') + 1, std::string::npos );
  
  
  std::string MC_Eloss = kAddEloss? "Eloss":"noEloss";
  std::string MC_MS = kAddMSsmearing? "MS":"noMS";
  std::string Seed_Eloss = kAddElossHelix? "Eloss":"noEloss";
  std::string Seed_MS = kAddMSHelix? "MS":"noMS";
  std::string Kalman_Eloss = kAddElossKalman? "Eloss":"noEloss";
  std::string Kalman_MS = kAddMSKalman? "MS":"noMS";

  std::string filename = "MC_"+smear+"smear_"+MC_Eloss+"_"+MC_MS+"_Seed_"+Seed_Eloss+"_"+Seed_MS+"_Kalman_"+Kalman_Eloss+"_"+Kalman_MS;
  std::string path ="/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/data/testTPCVSGarliteFull/";
  
  //std::string filename = "MC_01smear_noEloss_noMS_Seed_noEloss_noMS_Kalman_noEloss_noMS";
  //std::string path ="/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalman/data/testTPCmuons/fixedpt15/";
  std::string dirname = path+filename;
  std::string totalname = dirname +"/"+filename+".root";
  std::string filelist = dirname + "/fastParticle.list";
  const char* cdir = const_cast<char*>(dirname.c_str());
  const char* ctotal = const_cast<char*>(totalname.c_str());

  std::cout<< "Filename: "<<totalname<<std::endl;


  gSystem->mkdir(cdir,1);

  std::ofstream fw(filelist, std::ofstream::out);
  fw << totalname ;
  fw.close();

  ///read the tree source
  TChain* tree_source = new TChain("/anatree/GArAnaTree");    
  tree_source->Add("/home/federico/Documents/Universita/Federico_2020-2021/OxfordCode/Kalman_Garlite/MCgarlite/6planes/muon_test_ana10k*");
  std::vector<int>     *PDG = 0;
  std::vector<float>   *MCPStartX = 0;
  std::vector<float>   *MCPStartY = 0;
  std::vector<float>   *MCPStartZ = 0;
  std::vector<float>   *MCPStartPX = 0;
  std::vector<float>   *MCPStartPY = 0;
  std::vector<float>   *MCPStartPZ = 0;
  TBranch        *b_PDG;   //!
  TBranch        *b_MCPStartX;   //!
  TBranch        *b_MCPStartY;   //!
  TBranch        *b_MCPStartZ;   //!
  TBranch        *b_MCPStartPX;   //!
  TBranch        *b_MCPStartPY;   //!
  TBranch        *b_MCPStartPZ;   //!
  tree_source->SetBranchAddress("PDG", &PDG, &b_PDG);
  tree_source->SetBranchAddress("MCPStartX", &MCPStartX, &b_MCPStartX);
  tree_source->SetBranchAddress("MCPStartY", &MCPStartY, &b_MCPStartY);
  tree_source->SetBranchAddress("MCPStartZ", &MCPStartZ, &b_MCPStartZ);
  tree_source->SetBranchAddress("MCPStartPX", &MCPStartPX, &b_MCPStartPX);
  tree_source->SetBranchAddress("MCPStartPY", &MCPStartPY, &b_MCPStartPY);
  tree_source->SetBranchAddress("MCPStartPZ", &MCPStartPZ, &b_MCPStartPZ);

  int nParticlesSource = tree_source->GetEntries();

  nParticles = std::min(nParticles,nParticlesSource);
  
  
  TTreeSRedirector *pcstream = new TTreeSRedirector(ctotal,"recreate");
  TTree * tree = 0;
  int counter = 0;
  for (Int_t i=0; i<nParticles; i++){
    fastParticle particle(nPoints+1);
 
    tree_source->GetEntry(i);

    ////Parameters that regulate the simulation
    //const Float_t kResol=0.01;      
    particle.fAddEloss=kAddEloss;
    particle.fAddMSsmearing=kAddMSsmearing;
    particle.fAddElossGausssmearing=false;
    particle.fAddElossLandausmearing=false;

    ////Parameters that regulate the seeding
    particle.fAddElossHelix=kAddElossHelix;
    particle.fAddMSHelix=kAddMSHelix;

    ////Parameters that regulate the Kalman Filter Reconstruction
    particle.fAddElossKalman=kAddElossKalman;
    particle.fAddMSKalman=kAddMSKalman;
    



    particle.fgStreamer=pcstream;
    particle.gid=i;
    // generate scan detector properties
    for (Int_t iLayer=0; iLayer<geom.fLayerX0.size();iLayer++) {
      geom.fLayerX0[iLayer] = xx0 * kMaterialScaling;
      geom.fLayerRho[iLayer] = xrho * kMaterialScaling;
      geom.fLayerResolRPhi[iLayer] =resol[0];
      geom.fLayerResolZ[iLayer] = resol[1];
    }


    //define particle
    double r[]  = {-276,MCPStartY->at(0)-GArCenter[1],MCPStartX->at(0)-GArCenter[0]};        
    double p[]  = {MCPStartPZ->at(0),MCPStartPY->at(0),MCPStartPX->at(0)};
    long   pdgCode = PDG->at(0);
    //long   pdgCode = 2212;

    std::cout<<"Entry = "<<i<<"/"<<nParticles<<" r = ["<<r[0]<<", "<<r[1]<<", "<<r[2]<<"]  p = ["<<p[0]<<", "<<p[1]<<", "<<p[2]<<"] PDG = "<<pdgCode<<std::endl;
    
    particle.fDecayLength=0;                                                //don't decay particles

    float recostatus = 0;
    particle.simulateParticleOptions(geom, r,p,pdgCode, nPoints,nPoints);
    //recostatus = particle.reconstructParticleOptions(geom,pdgCode,nPoints);
    recostatus = particle.reconstructParticleOptionsFull(geom,pdgCode,nPoints);
    if (recostatus<0) counter++;

    //particle.reconstructParticleRotate0(geom,pdgCode,nLayerTPC);
    //particle.simulateParticle(geom, r,p,211, 250,161);
    //particle.reconstructParticle(geom,211,160);
    if (dumpStream==kFALSE) continue;
    if (tree) tree->Fill();
    else {
      (*pcstream) << "fastPart" <<
                  "i=" << i <<
                  "geom.="<<&geom<<
                  "pdgCode="<<pdgCode<<
                  "part.=" << &particle <<
                  "\n";
      tree=  ((*pcstream) << "fastPart").GetTree();
    }
  }
  delete pcstream;
  std::cout<<"Failed recos: "<<counter<<std::endl;
  timer.Print();
}