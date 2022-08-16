#ifndef fastTracker_H
#define fastTracker_H
/*
 .L $fastMCKalman/fastMCKalman/MC/fastTracker.h
 code based on the AliTPCtracker.
*/
// basic tracking functionality extracked
// https://github.com/miranov25/AliRoot/blob/master/TPC/TPCrec/AliTPCtracker.cxx#L1325
// https://github.com/miranov25/AliRoot/blob/2f249b4d1cff4e54e0b17f2b23ddb4d9b5e4bd9e/STEER/ESD/AliTrackerBase.cxx#L673
#include "AliExternalTrackParam.h"

class fastTracker{
public:
  static AliExternalTrackParam* makeSeed(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz);
  static AliExternalTrackParam* makeSeedMB(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz, float xx0, float xrho, float mass,int nSteps=5);
  static AliExternalTrackParam* makeSeedMBOptions(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz, float xx0, float xrho, float mass,int nSteps=5,Bool_t Eloss=false, Bool_t MS=false);
  
  
  static Double_t makeC(Double_t x1,Double_t y1, Double_t x2,Double_t y2, Double_t x3,Double_t y3);     // F1
  static Double_t makeSnp(Double_t x1,Double_t y1,Double_t x2,Double_t y2,Double_t x3,Double_t y3);     // F2
  static Double_t makeTgln(Double_t x1,Double_t y1, Double_t x2,Double_t y2, Double_t z1,Double_t z2,Double_t c);   // F3n
};


//_____________________________________________________________________________
Double_t fastTracker::makeC(Double_t x1,Double_t y1, Double_t x2,Double_t y2, Double_t x3,Double_t y3){
  //-----------------------------------------------------------------
  // Initial approximation of the track curvature
  //-----------------------------------------------------------------
  x3 -=x1;
  x2 -=x1;
  y3 -=y1;
  y2 -=y1;
  //  
  Double_t det = x3*y2-x2*y3;
  if (TMath::Abs(det)<1e-10){
    return 100;
  }
  //
  Double_t u = 0.5* (x2*(x2-x3)+y2*(y2-y3))/det;
  Double_t x0 = x3*0.5-y3*u;
  Double_t y0 = y3*0.5+x3*u;
  Double_t c2 = 1/TMath::Sqrt(x0*x0+y0*y0);
  if (det<0) c2*=-1;
  return c2;
}


Double_t fastTracker::makeSnp(Double_t x1,Double_t y1, Double_t x2,Double_t y2, Double_t x3,Double_t y3){
  //-----------------------------------------------------------------
  // Initial approximation of the track snp at position x1
  //-----------------------------------------------------------------
  x3 -=x1;
  x2 -=x1;
  y3 -=y1;
  y2 -=y1;
  //  
  Double_t det = x3*y2-x2*y3;
  if (TMath::Abs(det)<1e-10) {
    return 100;
  }
  //
  Double_t u = 0.5* (x2*(x2-x3)+y2*(y2-y3))/det;
  Double_t x0 = x3*0.5-y3*u; 
  Double_t y0 = y3*0.5+x3*u;
  Double_t c2 = 1/TMath::Sqrt(x0*x0+y0*y0);
  if (det>0) c2*=-1;
  x0*=c2;  
  return x0;
}

//_____________________________________________________________________________
Double_t fastTracker::makeTgln(Double_t x1,Double_t y1, Double_t x2,Double_t y2,Double_t z1,Double_t z2,Double_t c){
  //-----------------------------------------------------------------
  // Initial approximation of the tangent of the track dip angle
  //-----------------------------------------------------------------
  Double_t d  =  TMath::Sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  if (TMath::Abs(d*c*0.5)>1) return 0;
  Double_t   angle2    = asin(d*c*0.5);

  angle2  = (z1-z2)*c/(angle2*2.);    //dz /(R*dPhi)
  return angle2;
  //return (z1 - z2)/sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

AliExternalTrackParam * fastTracker::makeSeed(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz){
  Double_t sy2=sy*sy;
  Double_t sz2=sz*sz;
  Double_t param[5];
  Double_t c[15];
  // calculate initial param
  param[0]=xyz0[1];              
  param[1]=xyz0[2];
  param[2]=makeSnp(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz2[0],xyz2[1]);
  param[4]=makeC(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz2[0],xyz2[1]);
  param[3]=makeTgln(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz0[2],xyz1[2],param[4]);
  // x[3]=F3n(x1,y1,x2,y2,z1,z2,x[4]);
  // x[4]=F1(x1,y1,x2,y2,x3,y3);
  //
  Double_t f40=(makeC(xyz0[0],xyz0[1]+sy,xyz1[0],xyz1[1],xyz2[0],xyz2[1])-param[4])/sy;
  Double_t f42=(makeC(xyz0[0],xyz0[1],xyz1[0],xyz1[1]+sy,xyz2[0],xyz2[1])-param[4])/sy;
  Double_t f43=(makeC(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz2[0],xyz2[1]+sy)-param[4])/sy;
  //
  Double_t f20=(makeSnp(xyz0[0],xyz0[1]+sy,xyz1[0],xyz1[1],xyz2[0],xyz2[1])-param[2])/sy;
  Double_t f22=(makeSnp(xyz0[0],xyz0[1],xyz1[0],xyz1[1]+sy,xyz2[0],xyz2[1])-param[2])/sy;
  Double_t f23=(makeSnp(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz2[0],xyz2[1]+sy)-param[2])/sy;
  //
  //  makeTgln(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz0[2],xyz1[2],param[4]);
  Double_t f30=(makeTgln(xyz0[0],xyz0[1]+sy,xyz1[0],xyz1[1],xyz0[2],xyz1[2],param[4])-param[3])/sy;
  Double_t f31=(makeTgln(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz0[2]+sz,xyz1[2],param[4])-param[3])/sz;
  Double_t f32=(makeTgln(xyz0[0],xyz0[1],xyz1[0],xyz1[1]+sy,xyz0[2],xyz1[2],param[4])-param[3])/sy;
  Double_t f34=(makeTgln(xyz0[0],xyz0[1],xyz1[0],xyz1[1],xyz0[2],xyz1[2]+sz,param[4])-param[3])/sz;
  /*
  c[0]=sy2;
  c[1]=0.;       c[2]=sz2;
  c[3]=f20*sy2;   c[4]=0.;       c[5]=f20*sy2*f20+f22*sy2*f22+f23*sy2*f23;
  c[6]=f30*sy2;  c[7]=f31*sz2;  c[8]=f30*sy2*f20+f32*sy2*f22;
  c[9]=f30*sy2*f30+f31*sz2*f31+f32*sy2*f32+f34*sz2*f34;
  c[10]=f40*sy2; c[11]=0.; c[12]=f40*sy2*f20+f42*sy2*f22+f43*sy2*f23;
  c[13]=f30*sy2*f40+f32*sy2*f42;
  c[14]=f40*sy2*f40+f42*sy2*f42+f43*sy2*f43;
  
  */
  c[0]=sy2;
  c[1]=0.;       c[2]=sz2;
  c[3]=0.;       c[4]=0.;       c[5]=f20*sy2*f20+f22*sy2*f22+f23*sy2*f23;
  c[6]=0.;       c[7]=0.;       c[8]=0.;
  c[9]=f30*sy2*f30+f31*sz2*f31+f32*sy2*f32+f34*sz2*f34;
  c[10]=0.; c[11]=0.; c[12]=0.;
  c[13]=0.;
  c[14]=f40*sy2*f40+f42*sy2*f42+f43*sy2*f43;
  /////test
  

  if (TMath::Abs(bz)>kAlmost0Field) {
    c[14]/=(bz*kB2C)*(bz*kB2C);
    c[12]/=(bz*kB2C);
    c[10]/=(bz*kB2C);
    param[4]/=(bz*kB2C); // transform to 1/pt
  }
  else { // assign 0.6 GeV pT
    const double kq2pt = 1./0.6;
    param[4] = kq2pt;
    c[14] = (0.5*0.5)*kq2pt;
  }

  //
  //AliExternalTrackParam *param=new AliExternalTrackParam(
  //AliExternalTrackParam AliExternalTrackParam(Double_t x, Double_t alpha, const Double_t[5] param, const Double_t[15] covar)
  AliExternalTrackParam *extParam=new AliExternalTrackParam(xyz0[0],0,param,c);
  return extParam;
}

/// make seed correcting for the material budget  -assuming particle mass and mean x0 and density
/// \param xyz0
/// \param xyz1
/// \param xyz2
/// \param sy
/// \param sz
/// \param bz
/// \param xx0tocm
/// \param xrhotocm
/// \param mass
/// \return
AliExternalTrackParam* fastTracker::makeSeedMB(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz, float xx0tocm, float xrhotocm, float mass, int nSteps){
  // calculate momentum loss between the seeding points
  // linear approximation   p0 -> p1 -> p2
  // in case seeding radius is homogenous - pSeed ~ (p0+p1+p2)/3    p0~ pSeed*3-p1-p2
  // in case different gaps - TODO later
  AliExternalTrackParam *extParam = makeSeed(xyz0,xyz1,xyz2,sy,sz,bz);   // first estimation
  AliExternalTrackParam paramFull=*extParam;
  Double_t *xyz[3]={xyz0,xyz1,xyz2};
  Double_t deltaCovar[15];

  Bool_t propStatus=kTRUE;
  Double_t p0[3]={paramFull.Pt()};
  for (int i=1; i<3; i++) {
    propStatus &= paramFull.PropagateTo(xyz[i][0], bz);
    for (int iCovar = 0; iCovar < 15; iCovar++) deltaCovar[iCovar] = paramFull.GetCovariance()[iCovar];
    double crossLength = (xyz[i][0] - xyz[i - 1][0]) * (xyz[i][0] - xyz[i - 1][0]) +
                         (xyz[i][1] - xyz[i - 1][1]) * (xyz[i][1] - xyz[i - 1][1]) +
                         (xyz[i][2] - xyz[i - 1][2]) * (xyz[i][2] - xyz[i - 1][2]);
    crossLength = TMath::Sqrt(crossLength);
    for (int i = 0; i < nSteps; i++) {
      propStatus &= paramFull.CorrectForMeanMaterial(crossLength * xx0tocm / nSteps, crossLength * xrhotocm / nSteps, mass, kFALSE);
      
    }
    p0[i]=paramFull.Pt();
    if (i == 1) {
      for (int iCovar = 0; iCovar < 15; iCovar++) {
        deltaCovar[iCovar] = paramFull.GetCovariance()[iCovar] - deltaCovar[iCovar];
      }
    }
  }
  // Formula below approximation in case equal material distance of seeding layer
  Double_t ratio1= p0[1]/p0[0];
  Double_t ratio2= p0[2]/p0[0];
  //Double_t p0N=3.*p0[0]/(ratio2+ratio1+1.);
  Double_t p0NRatio=3./(ratio2+ratio1+1.);
  /// This hack - we should get proper curvature/sagita formula
  //
  ((double*)extParam->GetParameter())[4]/=  p0NRatio;
  ((double*)extParam->GetCovariance())[5] +=deltaCovar[5];
  ((double*)extParam->GetCovariance())[9] +=deltaCovar[9];
  ((double*)extParam->GetCovariance())[14]+=deltaCovar[14];
  return extParam;
}


AliExternalTrackParam* fastTracker::makeSeedMBOptions(double xyz0[3], double xyz1[3], double xyz2[3], double sy, double sz, float bz, float xx0tocm, float xrhotocm, float mass, int nSteps,Bool_t Eloss, Bool_t MS){
  // calculate momentum loss between the seeding points
  // linear approximation   p0 -> p1 -> p2
  // in case seeding radius is homogenous - pSeed ~ (p0+p1+p2)/3    p0~ pSeed*3-p1-p2
  // in case different gaps - TODO later
  AliExternalTrackParam *extParam = makeSeed(xyz0,xyz1,xyz2,sy,sz,bz);   // first estimation
  AliExternalTrackParam paramFull=*extParam;
  Double_t *xyz[3]={xyz0,xyz1,xyz2};
  Double_t deltaCovar[15];
  Double_t deltaMS[15];

  Bool_t propStatus=kTRUE;
  Double_t p0[3]={paramFull.Pt()};
  for (int i=1; i<3; i++) {
    propStatus &= paramFull.PropagateTo(xyz[i][0], bz);
    for (int iCovar = 0; iCovar < 15; iCovar++) 
    {
      deltaCovar[iCovar] = paramFull.GetCovariance()[iCovar];
      deltaMS[iCovar] = 0.;
    }
    
    
    double crossLength = (xyz[i][0] - xyz[i - 1][0]) * (xyz[i][0] - xyz[i - 1][0]) +
                         (xyz[i][1] - xyz[i - 1][1]) * (xyz[i][1] - xyz[i - 1][1]) +
                         (xyz[i][2] - xyz[i - 1][2]) * (xyz[i][2] - xyz[i - 1][2]);
    crossLength = TMath::Sqrt(crossLength);

    
   

    for (int i = 0; i < nSteps; i++) {
      
      if ((crossLength * xx0tocm / nSteps) != 0) {
        //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
        Double_t p=paramFull.GetP();
        if (mass<0) p += p; // q=2 particle 
        Double_t p2=p*p;
        Double_t beta2=p2/(p2 + mass*mass);
        Double_t theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(crossLength * xx0tocm / nSteps);
        if (paramFull.GetUseLogTermMS()) {
          double lt = 1+0.038*TMath::Log(TMath::Abs(crossLength * xx0tocm / nSteps));
          if (lt>0) theta2 *= lt*lt;
        }
        if (mass<0) theta2 *= 4; // q=2 particle
        if(theta2<TMath::Pi()*TMath::Pi()) 
        {
          deltaMS[5] += theta2*((1.-paramFull.GetParameter()[2])*(1.+paramFull.GetParameter()[2]))*(1. + paramFull.GetParameter()[3]*paramFull.GetParameter()[3]);
          deltaMS[9] += theta2*(1. + paramFull.GetParameter()[3]*paramFull.GetParameter()[3])*(1. + paramFull.GetParameter()[3]*paramFull.GetParameter()[3]);
          deltaMS[13] += theta2*paramFull.GetParameter()[3]*paramFull.GetParameter()[4]*(1. + paramFull.GetParameter()[3]*paramFull.GetParameter()[3]);
          deltaMS[14] += theta2*paramFull.GetParameter()[3]*paramFull.GetParameter()[4]*paramFull.GetParameter()[3]*paramFull.GetParameter()[4];
        }
      }
      
      propStatus &= paramFull.CorrectForMeanMaterial(crossLength * xx0tocm / nSteps, crossLength * xrhotocm / nSteps, mass, kFALSE);

      
      
    }
    p0[i]=paramFull.Pt();
    if (i == 1) {
      for (int iCovar = 0; iCovar < 15; iCovar++) {
        
        deltaCovar[iCovar] = paramFull.GetCovariance()[iCovar] - deltaCovar[iCovar];
        
      }
    }
  }
  // Formula below approximation in case equal material distance of seeding layer
  Double_t ratio1= p0[1]/p0[0];
  Double_t ratio2= p0[2]/p0[0];
  //Double_t p0N=3.*p0[0]/(ratio2+ratio1+1.);
  Double_t p0NRatio=3./(ratio2+ratio1+1.);
  /// This hack - we should get proper curvature/sagita formula
  //
  if(Eloss)((double*)extParam->GetParameter())[4]/=  p0NRatio;
  if(MS)((double*)extParam->GetCovariance())[5] +=deltaCovar[5];
  if(MS)((double*)extParam->GetCovariance())[9] +=deltaCovar[9];
  //std::cout<<"Cov14: "<<((double*)extParam->GetCovariance())[14]<<std::endl;
  if(Eloss)((double*)extParam->GetCovariance())[14]+=deltaCovar[14];
  //std::cout<<"Cov14: "<<((double*)extParam->GetCovariance())[14]<<std::endl;
  if(!MS && Eloss)((double*)extParam->GetCovariance())[14]+=(-1*deltaMS[14]);
  //std::cout<<"Cov14: "<<((double*)extParam->GetCovariance())[14]<<std::endl;

  return extParam;
}



#endif