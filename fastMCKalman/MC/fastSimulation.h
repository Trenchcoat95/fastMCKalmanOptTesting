#ifndef fastSimulation_H
#define fastSimulation_H

#include "TObject.h"
#include "AliExternalTrackParam.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
#include "ROOT/RVec.hxx"

class TTree;
//using namespace ROOT;
using namespace ROOT::VecOps;
const Int_t kMaxLayers=10000;
#pragma link C++ class RVec<AliExternalTrackParam>+;
#pragma link C++ class RVec<AliExternalTrackParam4D>+;
#pragma link C++ class RVec<int>+;
//#pragma link C++ class std::vector<int>;
//#pragma link C++ class RVec<std::vector<int>>;

class TTreeSRedirector;
Float_t fracUnitTest=0.1;

class AliExternalTrackParam4D: public AliExternalTrackParam{
public:
  AliExternalTrackParam4D();
  AliExternalTrackParam4D(const AliExternalTrackParam &, Double_t mass,Int_t z);
  virtual ~AliExternalTrackParam4D(){}
  Double_t Beta(){ Double_t p2=GetP();p2*=p2; return TMath::Sqrt(p2/(p2+fMass*fMass));}
  Double_t GetOverThr(Float_t sigma=0.01, Float_t width=0.0005, Float_t threshold=0.1);
  //
  Bool_t PropagateTo(Double_t xk, Double_t b, Int_t timeDir);
  Bool_t GetXYZatR(Double_t xr,Double_t bz, Double_t *xyz=0, Double_t* alpSect=0) const;
  //
  Bool_t CorrectForMeanMaterial(Double_t xOverX0, Double_t xTimesRho,Double_t mass,Float_t stepFraction=0.01,
	  Double_t (*f)(Double_t)=AliExternalTrackParam::BetheBlochSolid );
  Bool_t CorrectForMeanMaterialRK(Double_t xOverX0, Double_t xTimesRho,Double_t mass,Float_t stepFraction=0.01,
	  Double_t (*f)(Double_t)=AliExternalTrackParam::BetheBlochSolid );
  Bool_t CorrectForMeanMaterialRKv2(Double_t xOverX0, Double_t xTimesRho,Double_t mass, Float_t stepFraction=0.01,
	  Double_t (*f)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
   Bool_t CorrectForMeanMaterialT4(Double_t xOverX0, Double_t xTimesRho,Double_t mass, Double_t (*f)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  // dPdx function
  static Double_t dPdx(Double_t p, Double_t mass, Double_t (*fundEdx)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  static Double_t dPdxEuler(Double_t p, Double_t mass, Double_t xTimesRho, Double_t (*fundEdx)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  static Double_t dPdxEulerStep(Double_t p, Double_t mass, Double_t xTimesRho, Double_t step,  Double_t (*fundEdx)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  static Double_t dPdxCorrT4(Double_t p, Double_t mass, Double_t xTimesRho,Double_t (*fundEdx)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  static Double_t dPdxCorrT42(Double_t p, Double_t mass, Double_t xTimesRho,Double_t (*fundEdx)(Double_t)=AliExternalTrackParam::BetheBlochSolid);
  // Uit test functions
  void UnitTestDumpCorrectForMaterial(TTreeSRedirector * pcstream, Double_t xOverX0, Double_t xTimesRho,Double_t mass, Int_t nSteps, Float_t stepFraction=0.02);
public:
  Int_t    fZ;         // particle Z
  Double_t fMass;      // particle mass
  Double_t fLength;    // track length
  Double_t fTime;      // track time
  ClassDef(AliExternalTrackParam4D, 1)
};

class fastGeometry:public TObject{
public:
  fastGeometry():TObject(){}
  ~fastGeometry(){}
  fastGeometry(Int_t maxLayer){
    fLayerRadius.resize(maxLayer); fLayerX0.resize(maxLayer);fLayerRho.resize(maxLayer);fLayerIndex.resize(maxLayer);fLayerResolRPhi.resize(maxLayer);fLayerResolZ.resize(maxLayer);
  }
  void setLayerRadiusPower(int layer0, int layerN, float r0, float rN, float power, float X0,float rho, float resol[2]);
  void setLayer(int layer, float r0,  float X0,float rho, float resol[2]);
  void Print();
  RVec<float> fLayerRadius;        //   barrel radius array
  RVec<int>   fLayerIndex;         //   barrel indices for fast navigation
  RVec<float> fLayerX0;            //   barrel X0 array
  RVec<float> fLayerRho;           //   barrel Rho array
  RVec<float> fLayerResolRPhi;     //   r-phi resolution at layer
  RVec<float> fLayerResolZ;        //   z  resolution at layer
  RVec<float> fHitDensity;         //   hit density (hits per cm^2)
  float       fBz;                 //   magnetic field
  ClassDef(fastGeometry, 1)
};

class fastParticle : public TObject{
public:
  enum TrackingBits {
  kTrackRotate   = 0x1,
  kTrackPropagate  = 0x2,
  kTrackCorrectForMaterial =0x4,
  kTrackUpdate =0x8,
  kTrackChi2   =0x10
} ;

  fastParticle():TObject(){}
  ~fastParticle(){}
  fastParticle(int nLayers){
    fLayerIndex.reserve(nLayers); fDirection.reserve(nLayers); fParamIn.reserve(nLayers); fParamInRot.reserve(nLayers);
    fParamOut.reserve(nLayers); fParamMC.reserve(nLayers);fStatusMaskMC.reserve(nLayers); fStatusMaskIn.reserve(nLayers);
    fChi2.resize(nLayers);fLoop.reserve(nLayers);
    fMaxLayer=0;
  }
  int simulateParticle(fastGeometry     &geom, double r[3], double p[3], int pdgCode, float maxLength, int maxPoints);
  int reconstructParticle(fastGeometry  &geom, int pdgCode, uint layerStart);
  int reconstructParticleRotate0(fastGeometry  &geom, int pdgCode, uint layerStart);
  static void setAliases(TTree & tree);           //   set aliases for derived variables
  double fR[3];                            //   initial position
  double fP[3];                            //   initial momentum
  int                         fPdgCodeMC;  //   PDG code used in simulation
  int                         fPdgCodeRec; //   PDG code as used in reconstruction
  int                         fMaxLayer;   //   maximal layer position
  int                         fMaxLayerRec;   //   maximal layer position in reconstruction
  int                         fLengthIn;   //   track length for in propagation
   int                         fLengthInRot;   //   track length for in propagation
  RVec<int>                   fLayerIndex; //   layer index    - important for looper
  RVec<float>                  fDirection;  //   particle direction - Out=1, In = -1
  RVec<int>                   fLoop;          //   particle loop counter
  RVec<AliExternalTrackParam4D> fParamMC;    //   "simulate"      Param MC
  RVec<AliExternalTrackParam4D> fParamOut;   //   "reconstructed" Param Out
  RVec<AliExternalTrackParam4D> fParamIn;    //   "reconstructed" Param In
  RVec<AliExternalTrackParam4D> fParamInRot;    //   "reconstructed" Param In - in rotated frame
  RVec<int>      fStatusMaskMC;     //   rotation(0x1)/propagation(0x2)/correct for material(0x4)/update(0x8)
  RVec<int>      fStatusMaskIn;     //   rotation(0x1)/propagation(0x2)/correct for material(0x4)/update(0x8)
  RVec<int>      fStatusMaskInRot;     //   rotation(0x1)/propagation(0x2)/correct for material(0x4)/update(0x8)
  RVec<float>                 fChi2;      //   chi2  at layer
  //                                       - local information - to be assigned to simulated track - if not set  taken symmetric from fastGeometry
  RVec<float> fLayerResolRPhi;             //   r-phi resolution at layer
  RVec<float> fLayerResolZ;                //   z  resolution at layer
  RVec<float> fLayerDeltaRPhi;             //   r-phi delta distortion at layer
  RVec<float> fLayerDeltaZ;                //   z  delta distortion at layer
  RVec<float> fLayerProb;                  //   probability  to assign point
  RVec<float> fHitDensity;                 //   hit density
  RVec<bool> fLayerInDead;                 //   flag in that region
  static TTreeSRedirector * fgStreamer;    //   debug streamer
  ClassDef(fastParticle, 1)
};


#endif

