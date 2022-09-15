/*
    .L $fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.cxx+
    geom= fastGeometry(201.)
    particle=fastParticle(200);
    geom.setLayerRadiusPower(0,10,1,20,1.2,0);
    geom.setLayerRadiusPower(11,200,20,150,1.2,0);
*/

#include "fastSimulation.h"
//#include "AliHelix.h"
#include "TTreeStream.h"
#include "TRandom.h"
#include "fastTracker.h"


TTreeSRedirector* fastParticle::fgStreamer = nullptr;

ClassImp(fastGeometry)
ClassImp(fastParticle)
ClassImp(AliExternalTrackParam4D)


AliExternalTrackParam4D::AliExternalTrackParam4D():
  AliExternalTrackParam(),
  fZ(1),
  fMass(0),
  fLength(0),
  fTime(0){

}
AliExternalTrackParam4D::AliExternalTrackParam4D(const AliExternalTrackParam &t,Double_t mass,Int_t z):
  AliExternalTrackParam(t),
  fZ(z),
  fMass(mass),
  fLength(0),
  fTime(0){
}

AliExternalTrackParam4D::~AliExternalTrackParam4D(){};

/// Estimate shape size for particle - shape is determined by the diffusion, angles and deposited charge
/// \param sigma           -  diffusion sigma ~ induction gap - if as in the TPC
/// \param width           -  pixel width
/// \param threshold       -  threhsold in units of MIP
/// \return                - mean number of pixels above threshold
Double_t AliExternalTrackParam4D::GetOverThr(Float_t sigma, Float_t width, Float_t threshold){

}


/// propagate to radius and update Track length and time
/// \param xk
/// \param b
/// \param timeDir
/// \return
Bool_t AliExternalTrackParam4D::PropagateTo(Double_t xk, Double_t b, Int_t timeDir){
  static const Double_t kcc = 2.99792458e-2;
  Double_t xyzIn[3],xyzOut[3];
  GetXYZ(xyzIn);
  AliExternalTrackParam::PropagateTo(xk,b);
  GetXYZ(xyzOut);
  Double_t length=0;
  for (Int_t i=0;i<3;i++) length+=(xyzIn[i]-xyzOut[i])*(xyzIn[i]-xyzOut[i]);
  length=TMath::Sqrt(length);
  //
  fLength += length;
  Double_t p2inv = fP[4]*fP[4]/(1+fP[3]*fP[3]);
  Double_t mBeta = TMath::Sqrt( 1. + fMass*fMass*p2inv ); // 1/beta
  Double_t time = length * mBeta / kcc;
  fTime += timeDir*time;
}
///  Clone of the original method removing one protection - here we disable  TMath::Abs(cosT)>kAlmost1 check (lAlmost1 was very restrictive)
///  // This method has 3 modes of behaviour
///  // 1) xyz[3] array is provided but alpSect pointer is 0: calculate the position of track intersection
///  //    with circle of radius xr and fill it in xyz array
///  // 2) alpSect pointer is provided: find alpha of the sector where the track reaches local coordinate xr
///  //    Note that in this case xr is NOT the radius but the local coordinate.
///  //    If the xyz array is provided, it will be filled by track lab coordinates at local X in this sector
///  // 3) Neither alpSect nor xyz pointers are provided: just check if the track reaches radius xr
/// \param xr
/// \param bz
/// \param xyz
/// \param alpSect
/// \return
Bool_t AliExternalTrackParam4D::GetXYZatR(Double_t xr,Double_t bz, Double_t *xyz, Double_t* alpSect) const {
  double crv = GetC(bz);
  if ((TMath::Abs(bz)) < kAlmost0Field) crv = 0.;
  const double &fy = fP[0];
  const double &fz = fP[1];
  const double &sn = fP[2];
  const double &tgl = fP[3];
  //
  // general circle parameterization:
  // x = (r0+tR)cos(phi0) - tR cos(t+phi0)
  // y = (r0+tR)sin(phi0) - tR sin(t+phi0)
  // where qb is the sign of the curvature, tR is the track's signed radius and r0
  // is the DCA of helix to origin
  //
  double tR = 1. / crv;            // track radius signed
  double cs = TMath::Sqrt((1 - sn) * (1 + sn));
  double x0 = fX - sn * tR;        // helix center coordinates
  double y0 = fy + cs * tR;
  double phi0 = TMath::ATan2(y0, x0);  // angle of PCA wrt to the origin
  if (tR < 0) phi0 += TMath::Pi();
  if (phi0 > TMath::Pi()) phi0 -= 2. * TMath::Pi();
  else if (phi0 < -TMath::Pi()) phi0 += 2. * TMath::Pi();
  double cs0 = TMath::Cos(phi0);
  double sn0 = TMath::Sin(phi0);
  double r0 = x0 * cs0 + y0 * sn0 - tR; // DCA to origin
  double r2R = 1. + r0 / tR;
  //
  //
  if (r2R < kAlmost0) return kFALSE;  // helix is centered at the origin, no specific intersection with other concetric circle
  if (!xyz && !alpSect) return kTRUE;
  double xr2R = xr / tR;
  double r2Ri = 1. / r2R;
  // the intersection cos(t) = [1 + (r0/tR+1)^2 - (r0/tR)^2]/[2(1+r0/tR)]
  double cosT = 0.5 * (r2R + (1 - xr2R * xr2R) * r2Ri);
  if ((cosT * cosT) >= 1.) {  /// TODO - fix protection or change calculation
    //    printf("Does not reach : %f %f\n",r0,tR);
    return kFALSE; // track does not reach the radius xr
  }
  //
  double t = TMath::ACos(cosT);
  if (tR < 0) t = -t;
  // intersection point
  double xyzi[3];
  xyzi[0] = x0 - tR * TMath::Cos(t + phi0);
  xyzi[1] = y0 - tR * TMath::Sin(t + phi0);
  if (xyz) { // if postition is requested, then z is needed:
    double t0 = TMath::ATan2(cs, -sn) - phi0;
    double z0 = fz - t0 * tR * tgl;
    xyzi[2] = z0 + tR * t * tgl;
  } else xyzi[2] = 0;
  //
  Local2GlobalPosition(xyzi, fAlpha);
  //
  if (xyz) {
    xyz[0] = xyzi[0];
    xyz[1] = xyzi[1];
    xyz[2] = xyzi[2];
  }
  //
  if (alpSect) {
    double &alp = *alpSect;
    // determine the sector of crossing
    double phiPos = TMath::Pi() + TMath::ATan2(-xyzi[1], -xyzi[0]);
    int sect = ((Int_t)(phiPos * TMath::RadToDeg())) / 20;
    alp = TMath::DegToRad() * (20 * sect + 10);
    double x2r, f1, f2, r1, r2, dx, dy2dx, yloc = 0, ylocMax = xr * TMath::Tan(TMath::Pi() / 18); // min max Y within sector at given X
    //
    while (1) {
      Double_t ca = TMath::Cos(alp - fAlpha), sa = TMath::Sin(alp - fAlpha);
      if ((cs * ca + sn * sa) < 0) {
        //AliDebug(1, Form("Rotation to target sector impossible: local cos(phi) would become %.2f", cs * ca + sn * sa));
        return kFALSE;
      }
      //
      f1 = sn * ca - cs * sa;
      if (TMath::Abs(f1) >= kAlmost1) {
        //AliDebug(1, Form("Rotation to target sector impossible: local sin(phi) would become %.2f", f1));
        return kFALSE;
      }
      //
      double tmpX = fX * ca + fy * sa;
      double tmpY = -fX * sa + fy * ca;
      //
      // estimate Y at X=xr
      dx = xr - tmpX;
      x2r = crv * dx;
      f2 = f1 + x2r;
      if (TMath::Abs(f2) >= kAlmost1) {
        //AliDebug(1, Form("Propagation in target sector failed ! %.10e", f2));
        return kFALSE;
      }
      r1 = TMath::Sqrt((1. - f1) * (1. + f1));
      r2 = TMath::Sqrt((1. - f2) * (1. + f2));
      dy2dx = (f1 + f2) / (r1 + r2);
      yloc = tmpY + dx * dy2dx;
      if (yloc > ylocMax) {
        alp += 2 * TMath::Pi() / 18;
        sect++;
      }
      else if (yloc < -ylocMax) {
        alp -= 2 * TMath::Pi() / 18;
        sect--;
      }
      else break;
      if (alp >= TMath::Pi()) alp -= 2 * TMath::Pi();
      else if (alp < -TMath::Pi()) alp += 2 * TMath::Pi();
      //      if (sect>=18) sect = 0;
      //      if (sect<=0) sect = 17;
    }
    //
    // if alpha was requested, then recalculate the position at intersection in sector
    if (xyz) {
      xyz[0] = xr;
      xyz[1] = yloc;
      if (TMath::Abs(x2r) < 0.001) xyz[2] = fz + dx * (r2 + f2 * dy2dx) * tgl;
      else {
        // for small dx/R the linear apporximation of the arc by the segment is OK,
        // but at large dx/R the error is very large and leads to incorrect Z propagation
        // angle traversed delta = 2*asin(dist_start_end / R / 2), hence the arc is: R*deltaPhi
        // The dist_start_end is obtained from sqrt(dx^2+dy^2) = x/(r1+r2)*sqrt(2+f1*f2+r1*r2)
        // Similarly, the rotation angle in linear in dx only for dx<<R
        double chord = dx * TMath::Sqrt(1 + dy2dx * dy2dx);   // distance from old position to new one
        double rot = 2 * TMath::ASin(0.5 * chord * crv); // angular difference seen from the circle center
        xyz[2] = fz + rot / crv * tgl;
      }
      Local2GlobalPosition(xyz, alp);
    }
  }
  return kTRUE;
  //
}
/// get radiial direction sign
Int_t AliExternalTrackParam4D::GetDirectionSign(){
  Float_t dir = GetX()*Px()+GetY()*Py();
  return (dir>0)? 1:-1;
}

/// Runge-Kuta energy loss correction  - https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
/// WARNING - we use strange ALICE convention signing Z==2 particle with negative mass - TODO - replace it with explicit Q
/// \param xOverX0        - X/X0, the thickness in units of the radiation length.
/// \param xTimesRho      - is the product length*density (g/cm^2).
//                        - It should be passed as negative when propagating tracks
//                        - from the interaction point to the outside of the central barrel.
/// \param mass           - the mass of this particle (GeV/c^2). Negative mass means charge=2 particle
/// \param f              - dEdx formula
/// \param stepFraction   - step fraction  - above some limits RungeKuta instead of the Euler Method used
/// \return  CorrectForMeanMaterial status  (kFalse - Failed, kTrue - Success)
Bool_t AliExternalTrackParam4D::CorrectForMeanMaterialRK(Double_t xOverX0, Double_t xTimesRho, Double_t mass, Float_t stepFraction, Double_t (*f)(Double_t)){
  //  Runge Kuttta integral p(x)
  //k_{1} is the slope at the beginning of the interval, using {\displaystyle y}y (Euler's method);
  //k_{2} is the slope at the midpoint of the interval, using {\displaystyle y}y and {\displaystyle k_{1}}k_{1};
  //k_{3} is again the slope at the midpoint, but now using {\displaystyle y}y and {\displaystyle k_{2}}k_{2};
  //k_{4} is the slope at the end of the interval, using {\displaystyle y}y and {\displaystyle k_{3}}k_{3}.
  const Double_t kBGStop=0.02;
  Double_t p=GetP();
  Double_t q=(mass<0)?2.:1.;   // q=2 particle in ALICE convention
  mass=TMath::Abs(mass);
  Double_t mass2=mass*mass;
  p*=q;
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t p2=p*p;
  Double_t dEdxM=f(p/mass),dEdxMRK=0;
  Double_t Ein=TMath::Sqrt(p2+mass2);
  Double_t Eout=0;
  //Runge-Kuta
  if ( TMath::Abs(dEdxM*xTimesRho) > 0.3*Ein ) return kFALSE; //30% energy loss is too much!
  if (TMath::Abs(dEdxM*xTimesRho)>stepFraction*Ein || (Ein+dEdxM*xTimesRho)<mass){
    Double_t E1=Ein,E2=0,E3=0,E4=0;
    Double_t k1=0,k2=0,k3=0,k4=0;
    k1=dEdxM;
    E2=E1+k1*xTimesRho*0.5;
    if (E2*E2/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k2=f(TMath::Sqrt(E2*E2/mass2-1.));
    E3=E1+k2*xTimesRho*0.5;
    if (E3*E3/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k3=f(TMath::Sqrt(E3*E3/mass2-1.));
    E4=E1+k3*xTimesRho;
    if (E4*E4/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k4 =f(TMath::Sqrt(E4*E4/mass2-1.));
    dEdxMRK=(k1+2.*k2+2.*k3+k4)/6.;
    Eout=E1+xTimesRho*dEdxMRK;
  }else{
    Eout=Ein+xTimesRho*dEdxM;
  }

  Double_t Emean=(Ein+Eout)*0.5;
  if (Emean<mass) {
    return kFALSE;
  }
  // Use mean values for p2, p and beta2
  p2=Emean*Emean-mass2;
  p =TMath::Sqrt(p2);
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t beta2=p2/(p2+mass2);
  //
  Double_t &fP2=fP[2];
  Double_t &fP3=fP[3];
  Double_t &fP4=fP[4];
  Double_t &fC22=fC[5];
  Double_t &fC33=fC[9];
  Double_t &fC43=fC[13];
  Double_t &fC44=fC[14];
  //
  //Calculating the multiple scattering corrections******************
  Double_t cC22 = 0.;
  Double_t cC33 = 0.;
  Double_t cC43 = 0.;
  Double_t cC44 = 0.;
  if (xOverX0 != 0) {
    //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
    Double_t theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(xOverX0);
    if (GetUseLogTermMS()) {
      double lt = 1+0.038*TMath::Log(TMath::Abs(xOverX0));
      if (lt>0) theta2 *= lt*lt;
    }
    theta2 *= q*q;    // q=2 particle
    if(theta2>TMath::Pi()*TMath::Pi()) return kFALSE;
    cC22 = theta2*((1.-fP2)*(1.+fP2))*(1. + fP3*fP3);
    cC33 = theta2*(1. + fP3*fP3)*(1. + fP3*fP3);
    cC43 = theta2*fP3*fP4*(1. + fP3*fP3);
    cC44 = theta2*fP3*fP4*fP3*fP4;
  }

  //Calculating the energy loss corrections************************
  Double_t cP4=1.;
  if ((xTimesRho != 0.) && (beta2 < 1.)) {
    Double_t dE=Eout-Ein;
    if ( (1.+ dE/p2*(dE + 2*Ein)) < 0. ) return kFALSE;
    cP4 = 1./TMath::Sqrt(1.+ dE/p2*(dE + 2*Ein));  //A precise formula by Ruben !
    //if (TMath::Abs(fP4*cP4)>100.) return kFALSE; //Do not track below 10 MeV/c -dsiable controlled by the BG cut
    // Approximate energy loss fluctuation (M.Ivanov)
    const Double_t knst=0.07; // To be tuned.
    Double_t sigmadE=knst*TMath::Sqrt(TMath::Abs(dE));
    cC44 += ((sigmadE*Ein/p2*fP4)*(sigmadE*Ein/p2*fP4));

  }

  //Applying the corrections*****************************
  fC22 += cC22;
  fC33 += cC33;
  fC43 += cC43;
  fC44 += cC44;
  fP4  *= cP4;
  CheckCovariance();
  return kTRUE;
}




/// Correct for mean material
/// WARNING - we use strange ALICE convention signing Z==2 particle with negative mass - TODO - replace it with explicit Q
/// \param xOverX0        - X/X0, the thickness in units of the radiation length.
/// \param xTimesRho      - is the product length*density (g/cm^2).
//                        - It should be passed as negative when propagating tracks
//                        - from the interaction point to the outside of the central barrel.
/// \param mass           - the mass of this particle (GeV/c^2). Negative mass means charge=2 particle
/// \param f              - dEdx formula
/// \param stepFraction   - step fraction  - above some limits RungeKuta instead of the Euler Method used
/// \return  CorrectForMeanMaterial status  (kFalse - Failed, kTrue - Success)
Bool_t AliExternalTrackParam4D::CorrectForMeanMaterial(Double_t xOverX0, Double_t xTimesRho, Double_t mass, Float_t stepFraction, bool addMSSmearing, Double_t (*f)(Double_t)){
  const Double_t kBGStop=0.02;
  Double_t p=GetP();
  Double_t q=(mass<0)?2.:1.;   // q=2 particle in ALICE convention
  mass=TMath::Abs(mass);
  Double_t mass2=mass*mass;
  p*=q;
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t p2=p*p;
  Double_t dEdxM=f(p/mass),dEdxMRK=0;
  Double_t Ein=TMath::Sqrt(p2+mass2);
  Double_t dP= dPdxEulerStep(p,mass,xTimesRho,stepFraction,f);
  if (dP==0) return kFALSE;
  Double_t pOut=p+dP;
  if ((pOut/mass)<kBGStop) return kFALSE;
  Double_t Eout=TMath::Sqrt(pOut*pOut+mass2);
  p=(p+pOut)*0.5;
  // Use mean values for p2, p and beta2
  p2=p*p;
  Double_t beta2=p2/(p2+mass2);
  //
  Double_t &fP2=fP[2];
  Double_t &fP3=fP[3];
  Double_t &fP4=fP[4];
  Double_t &fC22=fC[5];
  Double_t &fC33=fC[9];
  Double_t &fC43=fC[13];
  Double_t &fC44=fC[14];
  //
  //Calculating the multiple scattering corrections******************
  Double_t cC22 = 0.;
  Double_t cC33 = 0.;
  Double_t cC43 = 0.;
  Double_t cC44 = 0.;
  if (xOverX0 != 0) {
    //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
    Double_t theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(xOverX0);
    if (GetUseLogTermMS()) {
      double lt = 1+0.038*TMath::Log(TMath::Abs(xOverX0));
      if (lt>0) theta2 *= lt*lt;
    }
    theta2 *= q*q;    // q=2 particle
    if(theta2>TMath::Pi()*TMath::Pi()) return kFALSE;
    cC22 = theta2*((1.-fP2)*(1.+fP2))*(1. + fP3*fP3);
    cC33 = theta2*(1. + fP3*fP3)*(1. + fP3*fP3);
    cC43 = theta2*fP3*fP4*(1. + fP3*fP3);
    cC44 = theta2*fP3*fP4*fP3*fP4;
  }

  //Calculating the energy loss corrections************************
  Double_t cP4=1.;
  if ((xTimesRho != 0.) && (beta2 < 1.)) {
    Double_t dE=Eout-Ein;
    if ( (1.+ dE/p2*(dE + 2*Ein)) < 0. ) return kFALSE;
    cP4 = 1./TMath::Sqrt(1.+ dE/p2*(dE + 2*Ein));  //A precise formula by Ruben !
    //if (TMath::Abs(fP4*cP4)>100.) return kFALSE; //Do not track below 10 MeV/c -dsiable controlled by the BG cut
    // Approximate energy loss fluctuation (M.Ivanov)
    const Double_t knst=0.07; // To be tuned.
    Double_t sigmadE=knst*TMath::Sqrt(TMath::Abs(dE));
    cC44 += ((sigmadE*Ein/p2*fP4)*(sigmadE*Ein/p2*fP4));
  }

  //Applying the corrections*****************************
  if (addMSSmearing){
    const float kMaxP3=0.5;
    const float kMaxP4=0.3;
    if (TMath::Sqrt(cC44)>kMaxP4*TMath::Abs(fP4)) return kFALSE;
    Float_t p2New=fP[2]+gRandom->Gaus(0,TMath::Sqrt(cC22));
    Float_t dp3New=gRandom->Gaus(0,TMath::Sqrt(cC33));
    if (TMath::Abs(p2New)>1.) return kFALSE;
    if (TMath::Abs(dp3New)>kMaxP3) return kFALSE;
    fP[2]=p2New;
    fP[3]+=dp3New;
    fP[4]+=gRandom->Gaus(0,TMath::Sqrt(cC44));
  }
  fC22 += cC22;
  fC33 += cC33;
  fC43 += cC43;
  fC44 += cC44;
  fP4  *= cP4;
  //CheckCovariance();
  return kTRUE;
}


/// Correct for mean material
/// WARNING - we use strange ALICE convention signing Z==2 particle with negative mass - TODO - replace it with explicit Q
/// \param xOverX0        - X/X0, the thickness in units of the radiation length.
/// \param xTimesRho      - is the product length*density (g/cm^2).
//                        - It should be passed as negative when propagating tracks
//                        - from the interaction point to the outside of the central barrel.
/// \param mass           - the mass of this particle (GeV/c^2). Negative mass means charge=2 particle
/// \param f              - dEdx formula
/// \param stepFraction   - step fraction  - above some limits RungeKuta instead of the Euler Method used
/// \return  CorrectForMeanMaterial status  (kFalse - Failed, kTrue - Success)
Bool_t AliExternalTrackParam4D::CorrectForMeanMaterialOptions(Double_t xOverX0, Double_t xTimesRho, Double_t mass, Float_t stepFraction, bool Reco, float sz,
                                                              bool addMSSmearing, bool addElossGaussSmearing, bool addElossLandauSmearing, Double_t (*f)(Double_t)){
  const Double_t kBGStop=0.0040;
  double pOld=GetP();
  Double_t p=GetP();
  Double_t q=(mass<0)?2.:1.;   // q=2 particle in ALICE convention
  mass=TMath::Abs(mass);
  Double_t mass2=mass*mass;
  p*=q;
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t p2=p*p;
  Double_t dEdxM=f(p/mass),dEdxMRK=0;
  Double_t Ein=TMath::Sqrt(p2+mass2);
  Double_t dP= dPdxEulerStep(p,mass,xTimesRho,stepFraction,f);
  
  if( addElossLandauSmearing)
  {
    //std::cout<<"dP: "<<dP;
    Double_t sign = TMath::Sign(1,dP);
    dP=gRandom->Landau(abs(dP),0.15*abs(dP));
    if (dP<0.0001) dP=0.0001;
    dP*=sign;
    //std::cout<<" dPsmear: "<<dP<<std::endl;
  }
  if(addElossGaussSmearing)
  {
    //std::cout<<"dP: "<<dP;
    Double_t sign = TMath::Sign(1,dP);
    dP=gRandom->Gaus(abs(dP),0.15*abs(dP));
    if (dP<0.0001) dP=0.0001;
    dP*=sign;
    //std::cout<<" dPsmear: "<<dP<<std::endl;
  }
  
  if (dP==0) return kFALSE;
  if (dP>0 && !Reco){
    ::Error("aliExternalTrackParam4D", "Incorrect energy loss %f -> %f ", p,dP);
    //dPdxEulerStep(p,mass,xTimesRho,stepFraction,f); //THIS was debug symbol - TODO remove it later
  }
  //std::cout<<"P: "<<p<<" dP: "<<dP<<std::endl;
  Double_t pOut=p+dP;
  if ((pOut/mass)<kBGStop) return kFALSE;
  Double_t Eout=TMath::Sqrt(pOut*pOut+mass2);
  p=(p+pOut)*0.5;
  // Use mean values for p2, p and beta2
  p2=p*p;
  Double_t beta2=p2/(p2+mass2);
  //
  Double_t &fP2=fP[2];
  Double_t &fP3=fP[3];
  Double_t &fP4=fP[4];
  Double_t &fC22=fC[5];
  Double_t &fC33=fC[9];
  Double_t &fC43=fC[13];
  Double_t &fC44=fC[14];
  //
  //Calculating the multiple scattering corrections******************
  Double_t cC22 = 0.;
  Double_t cC33 = 0.;
  Double_t cC43 = 0.;
  Double_t cC44 = 0.;
  Double_t theta2 = 0.;
  if (xOverX0 != 0 && addMSSmearing) {
    //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
    theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(xOverX0);
    if (GetUseLogTermMS()) {
      double lt = 1+0.038*TMath::Log(TMath::Abs(xOverX0));
      if (lt>0) theta2 *= lt*lt;
    }
    theta2 *= q*q;    // q=2 particle
    if(theta2>TMath::Pi()*TMath::Pi()) return kFALSE;
    cC22 = theta2*((1.-fP2)*(1.+fP2))*(1. + fP3*fP3);
    cC33 = theta2*(1. + fP3*fP3)*(1. + fP3*fP3);
    cC43 = theta2*fP3*fP4*(1. + fP3*fP3);
    cC44 = theta2*fP3*fP4*fP3*fP4;
  }

  //Calculating the energy loss corrections************************
  Double_t cP4=1.;
  Double_t dE = 0.;
  if ((xTimesRho != 0.) && (beta2 < 1.)) {
    dE=Eout-Ein;
    if ( (1.+ dE/p2*(dE + 2*Ein)) < 0. ) return kFALSE;
    cP4 = 1./TMath::Sqrt(1.+ dE/p2*(dE + 2*Ein));  //A precise formula by Ruben !
    //if (TMath::Abs(fP4*cP4)>100.) return kFALSE; //Do not track below 10 MeV/c -dsiable controlled by the BG cut
    // Approximate energy loss fluctuation (M.Ivanov)
    const Double_t knst=0.07; // To be tuned. usually 0.07
    Double_t sigmadE=knst*TMath::Sqrt(TMath::Abs(dE));
    cC44 += ((sigmadE*Ein/p2*fP4)*(sigmadE*Ein/p2*fP4));
  }

  //Applying the corrections*****************************

  if (addMSSmearing && !Reco ){
    const float kMaxP3=0.5;
    const float kMaxP4=0.3;
    if (TMath::Sqrt(cC44)>kMaxP4*TMath::Abs(fP4)) return kFALSE;
    Double_t p2New=fP[2]+gRandom->Gaus(0,TMath::Sqrt(cC22));
    Float_t  dp3New=gRandom->Gaus(0,TMath::Sqrt(cC33));
    if (TMath::Abs(p2New)>1.) return kFALSE;
    if (TMath::Abs(dp3New)>kMaxP3) return kFALSE;
    Double_t cP4MS = sqrt((1+(fP[3]+dp3New)*(fP[3]+dp3New))/(1+(fP[3])*(fP[3]))); ////keep total momentum constant for now
    fP[2]=p2New;
    fP[3]+=dp3New;
    fP[4]*=cP4MS;
    //float ran =  gRandom->Gaus(TMath::Sqrt(cC44),TMath::Sqrt(cC44));
    //if(ran>0) fP[4]+=ran*(fP[4]>0?1:-1);
    
    //fP[4]+=(fP[4]>0?1:-1)*abs(gRandom->Gaus(0,TMath::Sqrt(cC44)));
    // fP[4]+=gRandom->Gaus(0,TMath::Sqrt(cC44));  - TODO transform scattering in p2 and P3 to modification of qPt - can not be independent
  }

  
  const Double_t knstMS=10000; ////usually 0
  const Double_t knstEreco=0.0005; ////usually 0
  if(addMSSmearing && Reco && sz<0.1) cC44= knstMS*theta2*fP3*fP4*fP3*fP4+((knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4)*(knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4));
  if(!addMSSmearing && Reco && sz<0.1) cC44= ((knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4)*(knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4));
  
  if(addMSSmearing && Reco && sz<0.01) cC44= knstMS*theta2*fP3*fP4*fP3*fP4+((knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4)*(knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4));
  if(!addMSSmearing && Reco && sz<0.01) cC44= ((knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4)*(knstEreco*TMath::Sqrt(TMath::Abs(dE))*Ein/p2*fP4));
  

  fC22 += cC22;
  fC33 += cC33;
  fC43 += cC43;
  fC44 += cC44;
  fP4  *= cP4;

  if (!Reco && (GetP()>pOld) ){
    ::Error("AliExternalTrackParam4D", "Incorrect energy loss %f -> %f ", pOld,GetP());
  }

  
  //CheckCovariance();
  return kTRUE;
}



/// Runge-Kuta energy loss correction  - https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
/// WARNING - we use strange ALICE convention signing Z==2 particle with negative mass - TODO - replace it with explicit Q
/// \param xOverX0        - X/X0, the thickness in units of the radiation length.
/// \param xTimesRho      - is the product length*density (g/cm^2).
//                        - It should be passed as negative when propagating tracks
//                        - from the interaction point to the outside of the central barrel.
/// \param mass           - the mass of this particle (GeV/c^2). Negative mass means charge=2 particle
/// \param f              - dEdx formula
/// \param stepFraction   - step fraction
/// \return
Bool_t AliExternalTrackParam4D::CorrectForMeanMaterialRKv2(Double_t xOverX0, Double_t xTimesRho,Double_t mass, Float_t stepFraction,  Double_t (*f)(Double_t)){
  //  Runge Kuttta integral p(x)
  //k_{1} is the slope at the beginning of the interval, using {\displaystyle y}y (Euler's method);
  //k_{2} is the slope at the midpoint of the interval, using {\displaystyle y}y and {\displaystyle k_{1}}k_{1};
  //k_{3} is again the slope at the midpoint, but now using {\displaystyle y}y and {\displaystyle k_{2}}k_{2};
  //k_{4} is the slope at the end of the interval, using {\displaystyle y}y and {\displaystyle k_{3}}k_{3}.
  const Double_t kBGStop=0.02;
  Double_t p=GetP();
  Double_t q=(mass<0)?2.:1.;   // q=2 particle in ALICE convention
  mass=TMath::Abs(mass);
  Double_t mass2=mass*mass;
  p*=q;
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t p2=p*p;
  Double_t dEdxM=f(p/mass),dEdxMRK=0;
  Double_t Ein=TMath::Sqrt(p2+mass2);
  Double_t Eout=0;
  //Runge-Kutta
  if ( TMath::Abs(dEdxM*xTimesRho) > 0.3*Ein ) return kFALSE; //30% energy loss is too much!
  Double_t p2Mean=0, beta2Mean=0, mp2Beta2Mean=0;
  //
  Bool_t isRK=kFALSE;
  if (TMath::Abs(dEdxM*xTimesRho)>stepFraction*Ein || (Ein+dEdxM*xTimesRho)<mass){
    isRK=kTRUE;
    Double_t E1=Ein,E2=0,E3=0,E4=0;
    Double_t k1=0,k2=0,k3=0,k4=0;
    k1=dEdxM;
    E2=E1+k1*xTimesRho*0.5;
    if (E2*E2/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k2=f(TMath::Sqrt(E2*E2/mass2-1.));
    E3=E1+k2*xTimesRho*0.5;
    if (E3*E3/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k3=f(TMath::Sqrt(E3*E3/mass2-1.));
    E4=E1+k3*xTimesRho;
    if (E4*E4/mass2-1.< kBGStop*kBGStop) return kFALSE;
    k4 =f(TMath::Sqrt(E4*E4/mass2-1.));
    dEdxMRK=(k1+2.*k2+2.*k3+k4)/6.;
    Eout=E1+xTimesRho*dEdxMRK;
    //
    p2Mean=((E1*E1-mass2)+(E2*E2-mass2)+(E3*E3-mass2)+(E4*E4-mass2))*0.25;
    beta2Mean=((E1*E1-mass2)/(E1*E1)+(E2*E2-mass2)/(E2*E2)+(E3*E3-mass2)/(E3*E3)+(E4*E4-mass2)/(E4*E4))*0.25;
    //mp2Beta2Mean=1/(p2Mean*beta2Mean);
    //mp2Beta2Mean=((E1*E1-mass2)*(E1*E1-mass2)/(E1*E1)+(E2*E2-mass2)*(E2*E2-mass2)/(E2*E2)+(E3*E3-mass2)*(E3*E3-mass2)/(E3*E3)+(E4*E4-mass2)*(E4*E4-mass2)/(E4*E4))*0.25;
    mp2Beta2Mean=(1./((E1*E1-mass2)*(E1*E1-mass2)/(E1*E1))+2./((E2*E2-mass2)*(E2*E2-mass2)/(E2*E2))+2./((E3*E3-mass2)*(E3*E3-mass2)/(E3*E3))+1./((E4*E4-mass2)*(E4*E4-mass2)/(E4*E4)))/6.;
  }else{
    Eout=Ein+xTimesRho*dEdxM;
    p2Mean=((Ein*Ein-mass2)+(Eout*Eout-mass2))*0.5;
    beta2Mean=((Ein*Ein-mass2)/(Ein*Ein)+(Eout*Eout-mass2)/(Eout*Eout))*0.5;
    mp2Beta2Mean=1/(p2Mean*beta2Mean);
  }

  Double_t Emean=(Ein+Eout)*0.5;
  if (Emean<mass) {
    return kFALSE;
  }
  // Use mean values for p2, p and beta2
  p2=Emean*Emean-mass2;
  p =TMath::Sqrt(p2);
  if ((p/mass)<kBGStop) return kFALSE;
  Double_t beta2=p2/(p2+mass2);
  //
  Double_t &fP2=fP[2];
  Double_t &fP3=fP[3];
  Double_t &fP4=fP[4];
  Double_t &fC22=fC[5];
  Double_t &fC33=fC[9];
  Double_t &fC43=fC[13];
  Double_t &fC44=fC[14];
  //
  //Calculating the multiple scattering corrections******************
  Double_t cC22 = 0.;
  Double_t cC33 = 0.;
  Double_t cC43 = 0.;
  Double_t cC44 = 0.;
  if (xOverX0 != 0) {
    //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
    //Double_t theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(xOverX0);
    Double_t theta2=0.0136*0.0136*mp2Beta2Mean*TMath::Abs(xOverX0);
    if (GetUseLogTermMS()) {
      double lt = 1+0.038*TMath::Log(TMath::Abs(xOverX0));
      if (lt>0) theta2 *= lt*lt;
    }
    theta2 *= q*q;    // q=2 particle
    if(theta2>TMath::Pi()*TMath::Pi()) return kFALSE;
    cC22 = theta2*((1.-fP2)*(1.+fP2))*(1. + fP3*fP3);
    cC33 = theta2*(1. + fP3*fP3)*(1. + fP3*fP3);
    cC43 = theta2*fP3*fP4*(1. + fP3*fP3);
    cC44 = theta2*fP3*fP4*fP3*fP4;
  }

  //Calculating the energy loss corrections************************
  Double_t cP4=1.;
  if ((xTimesRho != 0.) && (beta2 < 1.)) {
    Double_t dE=Eout-Ein;
    if ( (1.+ dE/p2*(dE + 2.*Ein)) < 0. ) return kFALSE;
    cP4 = 1./TMath::Sqrt(1.+ dE/p2*(dE + 2.*Ein));  //A precise formula by Ruben !
    //if (TMath::Abs(fP4*cP4)>100.) return kFALSE; //Do not track below 10 MeV/c -dsiable controlled by the BG cut
    // Approximate energy loss fluctuation (M.Ivanov)
    const Double_t knst=0.07; // To be tuned.
    Double_t sigmadE=knst*TMath::Sqrt(TMath::Abs(dE));
    cC44 += ((sigmadE*Ein/p2*fP4)*(sigmadE*Ein/p2*fP4));

  }

  //Applying the corrections*****************************
  fC22 += cC22;
  fC33 += cC33;
  fC43 += cC43;
  fC44 += cC44;
  fP4  *= cP4;
  CheckCovariance();
  return kTRUE;
}


/// dPdx correction  on top of Euler approximation  - applying correction as in the dPdxCorr to correct - correction fitted in -0.25-0.25
/// \param xOverX0        - X/X0, the thickness in units of the radiation length.
/// \param xTimesRho      - is the product length*density (g/cm^2).
//                        - It should be passed as negative when propagating tracks
//                        - from the interaction point to the outside of the central barrel.
/// \param mass           - the mass of this particle (GeV/c^2). Negative mass means charge=2 particle
/// \param f              - dEdx formula
/// \return
Bool_t AliExternalTrackParam4D::CorrectForMeanMaterialT4(Double_t xOverX0, Double_t xTimesRho,Double_t mass,  Double_t (*f)(Double_t)){
  const Double_t kBGStop=0.02;
  //const Double_t kMaxdPdxRel=0.55, kMindPdxRel=-0.25; // relative correction fitted in that range
  const Double_t kMaxdPdxRel=0.55, kMindPdxRel=-0.55; // relative correction fitted in that range
  const Double_t kMaxLoss=0.6;
  Double_t p=GetP();
  Double_t q=(mass<0)?2.:1.;   // q=2 particle in ALICE convention
  mass=TMath::Abs(mass);
  p*=q;
  Double_t p2=p*p;
  Double_t dPdx=AliExternalTrackParam4D::dPdx(p,mass);
  if (dPdx==0) return kFALSE;
  Double_t dPdxRel=xTimesRho*dPdx/p;
  //if (dPdxRel>kMaxdPdxRel) return kFALSE;
  //if (dPdxRel<kMindPdxRel) return kFALSE;
  //
  Double_t corrPar[3] = {-1.59155, 3.84571,-3.93002};  // fitted in -0.25,0.55
  Double_t pVector[6];
  Double_t mp2Beta2Mean=0;
  Double_t sumW=0;
  for (Int_t i=5; i>=0;i--){
    dPdxRel=(dPdx*double(i)*xTimesRho*0.2)/p;
    Double_t dPdxRelCorr = dPdxRel * (1 + dPdxRel * (corrPar[0] + dPdxRel*(corrPar[1] + corrPar[2]*dPdxRel)));
    pVector[i]=(1+dPdxRelCorr)*p;
    if ((pVector[i]/mass)<kBGStop) return kFALSE;
    Double_t p2=pVector[i]*pVector[i];
    Double_t beta2=p2/(p2+mass*mass);
    Double_t w= (i==0 || i==5) ? 0.5:1.;
    mp2Beta2Mean+=w*(beta2*p2);
    sumW+=w;
  }
  mp2Beta2Mean/=sumW;
  Double_t pOut=pVector[5];
  Double_t Ein=TMath::Sqrt(p*p+mass*mass);
  Double_t Eout=TMath::Sqrt(pOut*pOut+mass*mass);
  Double_t dE=Eout-Ein;
  if (TMath::Log(pOut/p)>kMaxLoss) return kFALSE;
  //
  Double_t &fP2=fP[2];
  Double_t &fP3=fP[3];
  Double_t &fP4=fP[4];
  Double_t &fC22=fC[5];
  Double_t &fC33=fC[9];
  Double_t &fC43=fC[13];
  Double_t &fC44=fC[14];
  //
  //Calculating the multiple scattering corrections******************
  Double_t cC22 = 0.;
  Double_t cC33 = 0.;
  Double_t cC43 = 0.;
  Double_t cC44 = 0.;
  if (xOverX0 != 0) {
    //Double_t theta2=1.0259e-6*14*14/28/(beta2*p2)*TMath::Abs(d)*9.36*2.33;
    //Double_t theta2=0.0136*0.0136/(beta2*p2)*TMath::Abs(xOverX0);
    Double_t theta2=0.0136*0.0136*mp2Beta2Mean*TMath::Abs(xOverX0);
    if (GetUseLogTermMS()) {
      double lt = 1+0.038*TMath::Log(TMath::Abs(xOverX0));
      if (lt>0) theta2 *= lt*lt;
    }
    theta2 *= q*q;    // q=2 particle
    if(theta2>TMath::Pi()*TMath::Pi()) return kFALSE;
    cC22 = theta2*((1.-fP2)*(1.+fP2))*(1. + fP3*fP3);
    cC33 = theta2*(1. + fP3*fP3)*(1. + fP3*fP3);
    cC43 = theta2*fP3*fP4*(1. + fP3*fP3);
    cC44 = theta2*fP3*fP4*fP3*fP4;
  }

  //Calculating the energy loss corrections************************
  Double_t cP4=1.;
  if ((xTimesRho != 0.) ) {
    if ( (1.+ dE/p2*(dE + 2.*Ein)) < 0. ) return kFALSE;
    cP4 = 1./TMath::Sqrt(1.+ dE/p2*(dE + 2.*Ein));  //A precise formula by Ruben !
    //if (TMath::Abs(fP4*cP4)>100.) return kFALSE; //Do not track below 10 MeV/c -dsiable controlled by the BG cut
    // Approximate energy loss fluctuation (M.Ivanov)
    const Double_t knst=0.07; // To be tuned.
    Double_t sigmadE=knst*TMath::Sqrt(TMath::Abs(dE));
    cC44 += ((sigmadE*Ein/p2*fP4)*(sigmadE*Ein/p2*fP4));
  }

  //Applying the corrections*****************************
  fC22 += cC22;
  fC33 += cC33;
  fC43 += cC43;
  fC44 += cC44;
  fP4  *= cP4;
  CheckCovariance();
  return kTRUE;
}




/// First derivative of the dP/dx - for testing and visualization purposes
/// \param p       - particle momenta
/// \param mass    - particle mass
/// \param fdEdx   - dEdx function pointer
/// \return        - dP/dx
Double_t AliExternalTrackParam4D::dPdx(double p, double mass, Double_t (*fundEdx)(Double_t)){
    const Double_t kBGStop = 0.02;
    Double_t bg=p/mass;
    if (bg<kBGStop) return 0;
    Double_t dPdx=TMath::Abs(fundEdx(bg))*TMath::Sqrt(1.+1./(bg*bg));
    return dPdx;
};

/// first derivative of the dP/dx- Just for checking
/// \param p       - particle momenta
/// \param mass    - particle mass
/// \param fdEdx   - dEdx function pointer
/// \return        - dP/dx
Double_t AliExternalTrackParam4D::dPdxEuler(double p, double mass, Double_t xTimesRho, Double_t (*fundEdx)(Double_t)) {
  const Double_t kBGStop = 0.02;
  Double_t bg = p / mass;
  if (bg < kBGStop) return 0;
  Double_t dEdx = TMath::Abs(fundEdx(bg));
  Double_t E2 = TMath::Sqrt(p * p + mass * mass) + dEdx * xTimesRho;
  Double_t p2 = E2 * E2 - mass * mass;
  if (p2 < 0) return 0;
  return TMath::Sqrt(p2) - p;
}

/// First derivative of the dP/dx - for testing and visualization purposes
/// \param p       - particle momenta
/// \param mass    - particle mass
/// \param fdEdx   - dEdx function pointer
/// \return        - dP/dx
Double_t AliExternalTrackParam4D::dPdxEulerStep(double p, double mass,  Double_t xTimesRho, double step, Double_t (*fundEdx)(Double_t)){
    // const Double_t kBGStop=0.0040; // the position of non relybal BB  depends on the function ... not well defined BetheBlocAleph
    const Double_t kBGStop=0.0140;    // not well defined BetheBlocSolid
    Double_t bg=p/mass;
    double dEdxMin=fundEdx(3);
    float signCorr=(xTimesRho<0)? -1:1;
    double pOrig=p;
    if (bg<kBGStop) {
      return pOrig*signCorr;    /// if particle too low BG - we will let to loose full momenta
    }
    Double_t dPdx=TMath::Abs(fundEdx(bg))*TMath::Sqrt(1.+1./(bg*bg));

    Double_t dPdx2=TMath::Max(fundEdx(bg),dEdxMin)*TMath::Sqrt(1.+1./(bg*bg));
    //
    Int_t nSteps=1+(TMath::Abs(dPdx*xTimesRho)+TMath::Abs(dPdx2*xTimesRho))/step;
    if (nSteps==1) {
      float dP=0.5*(dPdx+dPdx2)*xTimesRho;
      if (abs(dP)>pOrig) return pOrig*signCorr;
      return dP; // can not loos more than full momenta -use linear approximation
    }
    Float_t xTimesRhoS=xTimesRho/nSteps;
    Float_t sumP=0;
    for (Int_t i=0; i<nSteps;i++){
      p+=dPdx*xTimesRhoS;
      sumP+=dPdx*xTimesRhoS;
      bg=p/mass;
      if (bg<kBGStop) return pOrig*signCorr;
      dPdx=TMath::Max(fundEdx(bg),dEdxMin)*TMath::Sqrt(1.+1./(bg*bg));
    }
    return TMath::Min(TMath::Abs(double(sumP)),pOrig)*signCorr;
};

/// dPdx - based on the first derivative of the dPdx corrected for "saturation" - see fit in the test_AliExternalTrackParam4D.C:fitdPdxScaling - for testing and visualization purposes
/// \param p       - particle momenta
/// \param mass    - particle mass
/// \param fdEdx   - dEdx function pointer
/// \return        - <dP/dx> *  xTimesRho
Double_t AliExternalTrackParam4D::dPdxCorrT4(double p, double mass, Double_t xTimesRho, Double_t (*fundEdx)(Double_t)) {
  const Double_t kBGStop = 0.02;
  Double_t corrPar[3] = {-1.59155, 3.84571,-3.93002};  // fitted in -0.25,0.55
  Double_t bg = p / mass;
  if (bg < kBGStop) return 0;
  Double_t dPdx = TMath::Abs(fundEdx(bg))*TMath::Sqrt(1. + 1. / (bg * bg));
  Double_t dPdxRel = (dPdx * xTimesRho) / p;
  if (dPdxRel>0.6) return 0;
  if (dPdxRel<-0.25) return 0;
  Double_t dPdxRelCorr = dPdxRel * (1 + dPdxRel * (corrPar[0] + dPdxRel*(corrPar[1] + corrPar[2]*dPdxRel)));
  return dPdxRelCorr * p;
}

/// dPdx - based on the first derivative of the dPdx corrected for "saturation" - see fit in the test_AliExternalTrackParam4D.C:fitdPdxScaling - for testing and visualization purposes
/// \param p       - particle momenta
/// \param mass    - particle mass
/// \param fdEdx   - dEdx function pointer
/// \return        - <dP/dx> *  xTimesRho
Double_t AliExternalTrackParam4D::dPdxCorrT42(double p, double mass, Double_t xTimesRho, Double_t (*fundEdx)(Double_t)) {
  const Double_t kBGStop = 0.02;
  Double_t corrParM[3] = {-1.046866,-0.075693,-26.008540};
  Double_t corrParP[3] = {-0.873142,0.562098,-0.131849};
  Double_t bg = p / mass;
  if (bg < kBGStop) return 0;
  Double_t dPdx = TMath::Abs(fundEdx(bg))*TMath::Sqrt(1. + 1. / (bg * bg));
  Double_t logP=TMath::Log(p);
  if ((dPdx * xTimesRho+p)<kBGStop*mass) return 0;
  Double_t dPdxLR = TMath::Log(dPdx * xTimesRho+p) - logP;
  if (dPdxLR>2) return 0;
  if (dPdxLR<-0.3) return 0;
  Double_t *corrPar = (dPdxLR<0) ? corrParM:corrParP;
  Double_t dPdxRelCorr = dPdxLR * (1 + dPdxLR * (corrPar[0] + dPdxLR*(corrPar[1] + corrPar[2]*dPdxLR)));
  Double_t pOut=p*(TMath::Exp(dPdxRelCorr)-1);
  return pOut;
}






/// Unit test to check performance  - tracks is corrected in nSteps or using RK in one step - the results will be stored in the streamer for later numberical analysis
/// \param pcstream       - debug streamer output
/// \param xOverX0        - X0
/// \param xTimesRho      - is the product length*density (g/cm^2).
/// \param mass           - particle mass
/// \param nSteps         - nsteps to be done for the refernce
/// \param stepFraction   - step fraction to switch between RK and Euler
void AliExternalTrackParam4D::UnitTestDumpCorrectForMaterial(TTreeSRedirector * pcstream, Double_t xOverX0, Double_t xTimesRho,Double_t mass,Int_t nSteps, Float_t stepFraction) {
  AliExternalTrackParam4D param0 = *this;
  AliExternalTrackParam4D paramRK = *this;
  AliExternalTrackParam4D paramRK2 = *this;
  AliExternalTrackParam4D paramE = *this;
  AliExternalTrackParam4D paramT4 = *this;
  AliExternalTrackParam4D paramStep = *this;
  AliExternalTrackParam4D paramStepRK = *this;
  //
  Int_t status0 = param0.CorrectForMeanMaterial(xOverX0, xTimesRho, mass);                         //  status for old Euler implementation
  Int_t statusE = paramE.CorrectForMeanMaterial(xOverX0, xTimesRho, mass, stepFraction);        //  status for Euler  implementation
  Int_t statusRK = paramRK.CorrectForMeanMaterialRK(xOverX0, xTimesRho, mass, stepFraction);        //  status for new RK  implementation
  Int_t statusRK2 = paramRK2.CorrectForMeanMaterialRKv2(xOverX0, xTimesRho, mass, stepFraction);      //  status for new RK with RK  implementation v2
   Int_t statusT4 = paramT4.CorrectForMeanMaterialT4(xOverX0, xTimesRho, mass);      //  status for new RK with RK in momentum
  Int_t statusStep = kTRUE;
  Int_t statusStepRK = kTRUE;
  for (Int_t iStep = 0; iStep < nSteps; iStep++) {
    statusStep &= paramStep.CorrectForMeanMaterial(xOverX0 / nSteps, xTimesRho / nSteps, mass);
    statusStepRK &= paramStepRK.CorrectForMeanMaterialRK(xOverX0 / nSteps, xTimesRho / nSteps, mass);
  }
  (*pcstream) << "UnitTestDumpCorrectForMaterial" <<
              "xOverX0=" << xOverX0 <<
              "xTimesRho=" << xTimesRho <<
              "mass=" << mass <<
              "nSteps=" << nSteps <<
              //
              "statusStep=" << statusStep <<
              "statusStepRK=" << statusStepRK <<
              "status0=" << status0 <<
              "statusRK=" << statusRK <<
              "statusRK2=" << statusRK2 <<
              "statusE=" << statusE <<
              "statusT4=" << statusT4 <<
              "paramIn.=" << this <<
              "param0.=" << &param0 <<
              "paramRK.=" << &paramRK <<
              "paramRK2.=" << &paramRK2 <<
              "paramE.=" << &paramE <<
              "paramT4.=" << &paramT4 <<
              "paramStep.=" << &paramStep <<
              "paramStepRK.=" << &paramStepRK <<
              "\n";
}

void getHelix(Double_t *fHelix,  AliExternalTrackParam t, float bz){
  // addapted code from AliHelix
  Double_t x,cs,sn;
  x=t.GetX();
  for (Int_t i=0;i<5; i++) fHelix[i]=t.GetParameter()[i];
  float alpha = t.GetAlpha();
  //
  //circle parameters
  //PH Sometimes fP4 and fHelix[4] are very big and the calculation
  //PH of the Sqrt cannot be done. To be investigated...
  fHelix[4]=fHelix[4]/(-1000/0.299792458/bz);    // C
  //  cs=TMath::Cos(alpha); sn=TMath::Sin(alpha);
  cs=cosf(alpha); sn=sinf(alpha); // RS use float versions: factor 2 in CPU speed
  Double_t xc, yc, rc;
  rc  =  1/fHelix[4];
  xc  =  x-fHelix[2]*rc;
  Double_t dummy = 1-(x-xc)*(x-xc)*fHelix[4]*fHelix[4];
  if (dummy<0) dummy = 0;
  yc  =  fHelix[0]+TMath::Sqrt(dummy)/fHelix[4];
  fHelix[6] = xc*cs - yc*sn;
  fHelix[7] = xc*sn + yc*cs;
  fHelix[8] =  TMath::Abs(rc);
  return;
}


/// make layer distribution in interval layer0(r0)->layerN(rN) following power low distance
/// \param layer0
/// \param layerN
/// \param r0
/// \param rN
/// \param power
/// \param X0
void fastGeometry::setLayerRadiusPower(int layer0, int layerN, float r0, float rN, float power, float X0,float rho, float resol[2]){
    float dLayerN=(layerN-layer0);
    for (Int_t iLayer=layer0; iLayer<=layerN; iLayer++){
        fLayerX0[iLayer]=X0;
        fLayerRho[iLayer]=rho;
        float radius=r0+TMath::Power(float(iLayer-layer0)/dLayerN,power)*(rN-r0);
        fLayerRadius[iLayer]=radius;
        fLayerResolRPhi[iLayer]=resol[0];
        fLayerResolZ[iLayer]=resol[1];
    }
    fLayerIndex = Argsort(fLayerRadius);
}

void fastGeometry::setLayer(int iLayer, float radius,  float X0,float rho, float resol[2]) {
  fLayerX0[iLayer] = X0;
  fLayerRho[iLayer] = rho;
  fLayerRadius[iLayer] = radius;
  fLayerResolRPhi[iLayer] = resol[0];
  fLayerResolZ[iLayer] = resol[1];
}

/// simulate particle    - barrel part, end cup and loopers not yet implemented
/// \param geom          - geometry and B field description
/// \param r             - initial position
/// \param p             - initial momenta
/// \param pdgCode       - PDG code of particle (pion, Kaon,proton,electron,muon)
/// \param maxLength     - max length to simulate
/// \param maxPoints     - maximal number of points to simulate
/// \return              - modify status of particles = create points along   - TODO status flags to be decides
int fastParticle::simulateParticle(fastGeometry  &geom, double r[3], double p[3], long pdgCode, float maxLength, int maxPoints){
  fMaxLayer=0;
  const float kMaxSnp=0.90;
  const float kMaxLoss=0.5;
   double covar[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   float_t mass=0,sign=1;
  fPdgCodeMC=pdgCode;
  if (pdgCode==0){
    fMassMC=gRandom->Rndm();
    mass=fMassMC;
    sign=-1+2*gRandom->Rndm();
  }else {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
    if (particle == nullptr) {
      ::Error("fastParticle::simulateParticle", "Invalid pdgCode %ld", pdgCode);
      return -1;
    }
    sign = particle->Charge() / 3.;
    mass = particle->Mass();
    fMassMC=mass;
  }
  AliExternalTrackParam param0(r,p,covar,sign);
  AliExternalTrackParam4D param(param0,mass,1);
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  float direction=r[0]*p[0]+r[1]*p[1]+r[2]*p[2];
  direction=(direction>0)? 1.:-1.;
  if (radius==0) direction=1;
  int loopCounter=0;
  uint indexR= uint(std::upper_bound (geom.fLayerRadius.begin(),geom.fLayerRadius.end(), radius)-geom.fLayerRadius.begin());
  int nPoint=0;
  fParamMC.resize(1);
  fParamMC[0]=param;
  fLayerIndex[0]=indexR;
  fDirection[0]=0;
  fLoop[0]=0;
  double *par = (double*)param.GetParameter();
  for (nPoint=1; nPoint<maxPoints&&length<maxLength; nPoint++){
    fLoop.resize(nPoint+1);
    fDirection.resize(nPoint+1);
    fStatusMaskMC.resize(nPoint+1);
    //printf("%d\n",nPoint);
    //param.Print();
    if (indexR>geom.fLayerRadius.size()) {
      break;
    }
    if (fStatusMaskMC.size()<=nPoint) fStatusMaskMC.resize(nPoint+1);
    //
    double xyz[3],pxyz[3];
    float radius  = geom.fLayerRadius[indexR];
    //float xrho    = geom.fLayerRho[indexR];
    //float xx0     = geom.fLayerX0[indexR];
    //Float_t x = param.GetXatLabR(r,localX,fBz,1);
    int status =  param.GetXYZatR(radius,geom.fBz,xyz);
    if (status==0){   // if not possible to propagate to next radius - assume looper - change direction
      //break;    //this is temporary
      param.GetPxPyPz(pxyz);
      float C         = param.GetC(geom.fBz);
      float R         = TMath::Abs(1/C);
      float dca       = param.GetD(0,0,geom.fBz);         // signed distance of closest approach to origin (0,0) -- looks like  buggy in some cases - dca can be negative with dca<2*R
      double helix[9];
      getHelix(helix,param,geom.fBz);
      double x0=helix[6],y0=helix[7],r0=TMath::Sqrt(x0*x0+y0*y0);
      float dcaMI     = r0-R;
      float dlaMI     = r0+R;
      float dla       = dca+2*R;                          // distance of longest approach
      int  isUp       = abs(radius-dcaMI)>abs(radius-dlaMI)? 1:0;
      int        aSign= (param.GetSnp()>0)? 1:-1.;
      float alpha     = param.GetAlpha();
      float alphaC    = TMath::ATan2(y0,x0);
      float dAlpha    = alpha-alphaC;
      if (dAlpha>TMath::Pi()) dAlpha-=TMath::TwoPi();
      if (dAlpha<-TMath::Pi()) dAlpha+=TMath::TwoPi();
      float alpha2 = alphaC-dAlpha;
      double param2[5];
      param2[0]=0;
      param2[1]=param.GetParameter()[1];
      param2[2]=-param.GetParameter()[2];
      param2[3]=-param.GetParameter()[3];
      param2[4]=-param.GetParameter()[4];
      AliExternalTrackParam paramNew(param.GetX(),alpha2,param2,param.GetCovariance());
      if (fgStreamer){
        (*fgStreamer)<<"turn"<<
          "radius="<<radius<<     // radius to propagate
          "direction="<<direction<<
          "x0="<<x0<<
          "y0="<<y0<<
          "dca="<<dca<<
          "dcaMI="<<dcaMI<<
          "dlaMI="<<dlaMI<<
          "param.="<<&param<<
          "paramNew.="<<&paramNew<<
          "\n";
      }
      param=AliExternalTrackParam4D(paramNew,mass,1);
      direction*=-1;
      fDirection[nPoint]=direction;
      loopCounter++;
      fLoop[nPoint]=loopCounter;
    }else{
      double alpha  = TMath::ATan2(xyz[1],xyz[0]);
      fStatusMaskMC[nPoint]=0;
      status = param.Rotate(alpha);
      if (status) {
        fStatusMaskMC[nPoint]|= kTrackRotate;
      }else{
        break;
      }
      status = param.PropagateTo(radius,geom.fBz,1);
      if (status) {
        fStatusMaskMC[nPoint]|=kTrackPropagate;
      }else{
        break;
      }
    }
    //
    float xrho    = geom.fLayerRho[indexR];
    float xx0     = geom.fLayerX0[indexR];
    float tanPhi2 = par[2]*par[2];
    tanPhi2/=(1-tanPhi2);
    float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);               /// geometrical path assuming crossing cylinder
    //status = param.CorrectForMeanMaterialT4(crossLength*xx0,-crossLength*xrho,mass);
    status = param.CorrectForMeanMaterial(crossLength*xx0,-crossLength*xrho,mass,0.005,fAddMSsmearing);
    if (gRandom->Rndm()<fracUnitTest) param.UnitTestDumpCorrectForMaterial(fgStreamer,crossLength*xx0,-crossLength*xrho,mass,20);
    if (status) {
        fStatusMaskMC[nPoint]|=kTrackCorrectForMaterial;
      }else{
        break;
    }
    fParamMC.resize(nPoint+1);
    fParamMC[nPoint]=param;
    fLayerIndex[nPoint]=indexR;
    fLoop[nPoint]=loopCounter;
    fDirection[nPoint]=direction;
    indexR+=direction;
    if (indexR>fMaxLayer) fMaxLayer=indexR;
    if (fDecayLength>0 &&param.fLength>fDecayLength) break;   // decay particles
  }
  return 1;
}


/// simulate particle    - barrel part, end cup and loopers not yet implemented
/// \param geom          - geometry and B field description
/// \param r             - initial position
/// \param p             - initial momenta
/// \param pdgCode       - PDG code of particle (pion, Kaon,proton,electron,muon)
/// \param maxLength     - max length to simulate
/// \param maxPoints     - maximal number of points to simulate
/// \return              - modify status of particles = create points along   - TODO status flags to be decides
int fastParticle::simulateParticleOptions(fastGeometry  &geom, double r[3], double p[3], long pdgCode, float maxLength, int maxPoints){
  fMaxLayer=0;
  const float kMaxSnp=0.90;
  const float kMaxLoss=0.5;
  bool Reco = false;

   double covar[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   float_t mass=0,sign=1;
  fPdgCodeMC=pdgCode;
  if (pdgCode==0){
    fMassMC=gRandom->Rndm();
    mass=fMassMC;
    sign=-1+2*gRandom->Rndm();
  }else {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
    if (particle == nullptr) {
      ::Error("fastParticle::simulateParticle", "Invalid pdgCode %ld", pdgCode);
      return -1;
    }
    sign = particle->Charge() / 3.;
    mass = particle->Mass();
    fMassMC=mass;
  }
  AliExternalTrackParam param0(r,p,covar,sign);
  AliExternalTrackParam4D param(param0,mass,1);
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  float direction=r[0]*p[0]+r[1]*p[1]+r[2]*p[2];
  direction=(direction>0)? 1.:-1.;
  if (radius==0) direction=1;
  int loopCounter=0;
  uint indexR= uint(std::upper_bound (geom.fLayerRadius.begin(),geom.fLayerRadius.end(), radius)-geom.fLayerRadius.begin());
  int nPoint=0;
  fParamMC.resize(1);
  fParamMC[0]=param;
  fLayerIndex[0]=indexR;
  fDirection[0]=0;
  fLoop[0]=0;
  double *par = (double*)param.GetParameter();
  for (nPoint=1; nPoint<maxPoints&&length<maxLength; nPoint++){
    fLoop.resize(nPoint+1);
    fDirection.resize(nPoint+1);
    fStatusMaskMC.resize(nPoint+1);
    //printf("%d\n",nPoint);
    //param.Print();
    if (indexR>=geom.fLayerRadius.size()) {
      break;
    }
    if (fStatusMaskMC.size()<=nPoint) fStatusMaskMC.resize(nPoint+1);
    //
    double xyz[3],pxyz[3];
    float radius  = geom.fLayerRadius[indexR];
    //float xrho    = geom.fLayerRho[indexR];
    //float xx0     = geom.fLayerX0[indexR];
    //Float_t x = param.GetXatLabR(r,localX,fBz,1);
    //float limit = geom.fLayerRadius.at(geom.fLayerRadius.size()-1);
    int status =  param.GetXYZatR(radius,geom.fBz,xyz);
    //if (radius==limit && status==0) {
    //  break;
    //}
    if (status==0){   // if not possible to propagate to next radius - assume looper - change direction
      //break;    //this is temporary
      param.GetPxPyPz(pxyz);
      float C         = param.GetC(geom.fBz);
      float R         = TMath::Abs(1/C);
      float dca       = param.GetD(0,0,geom.fBz);         // signed distance of closest approach to origin (0,0) -- looks like  buggy in some cases - dca can be negative with dca<2*R
      double helix[9];
      getHelix(helix,param,geom.fBz);
      double x0=helix[6],y0=helix[7],r0=TMath::Sqrt(x0*x0+y0*y0);
      float dcaMI     = r0-R;
      float dlaMI     = r0+R;
      float dla       = dca+2*R;                          // distance of longest approach
      int  isUp       = abs(radius-dcaMI)>abs(radius-dlaMI)? 1:0;
      int        aSign= (param.GetSnp()>0)? 1:-1.;
      float alpha     = param.GetAlpha();
      float alphaC    = TMath::ATan2(y0,x0);
      float dAlpha    = alpha-alphaC;
      if (dAlpha>TMath::Pi()) dAlpha-=TMath::TwoPi();
      if (dAlpha<-TMath::Pi()) dAlpha+=TMath::TwoPi();
      float alpha2 = alphaC-dAlpha;
      double param2[5];
      param2[0]=0;
      param2[1]=param.GetParameter()[1];
      param2[2]=-param.GetParameter()[2];
      param2[3]=-param.GetParameter()[3];
      param2[4]=-param.GetParameter()[4];
      AliExternalTrackParam paramNew(param.GetX(),alpha2,param2,param.GetCovariance());
      if (fgStreamer){
        (*fgStreamer)<<"turn"<<
          "radius="<<radius<<     // radius to propagate
          "direction="<<direction<<
          "x0="<<x0<<
          "y0="<<y0<<
          "dca="<<dca<<
          "dcaMI="<<dcaMI<<
          "dlaMI="<<dlaMI<<
          "param.="<<&param<<
          "paramNew.="<<&paramNew<<
          "\n";
      }
      param=AliExternalTrackParam4D(paramNew,mass,1);
      direction*=-1;
      fDirection[nPoint]=direction;
      loopCounter++;
      fLoop[nPoint]=loopCounter;
      status++;
    }else{
      double alpha  = TMath::ATan2(xyz[1],xyz[0]);
      fStatusMaskMC[nPoint]=0;
      status = param.Rotate(alpha);
      if (status) {
        fStatusMaskMC[nPoint]|= kTrackRotate;
      }else{
        break;
      }
      status = param.PropagateTo(radius,geom.fBz,1);
      if (status) {
        fStatusMaskMC[nPoint]|=kTrackPropagate;
      }else{
        break;
      }
    }
    //
    float xrho    = geom.fLayerRho[indexR];
    float xx0     = geom.fLayerX0[indexR];
    float tanPhi2 = par[2]*par[2];
    tanPhi2/=(1-tanPhi2);
    float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);               /// geometrical path assuming crossing cylinder
    //status = param.CorrectForMeanMaterialT4(crossLength*xx0,-crossLength*xrho,mass);
    double pOld=param.GetP();
    if(fAddEloss) status = param.CorrectForMeanMaterialOptions(crossLength*xx0,-crossLength*xrho,mass,0.005,Reco,10,fAddMSsmearing,fAddElossGausssmearing,fAddElossLandausmearing);
    if ((status == true) && param.GetP()>pOld){
      ::Error("simulateParticle", "Invalid momentum loss %f ->%f - check again",pOld,param.GetP());
      status = param.CorrectForMeanMaterialOptions(crossLength*xx0,-crossLength*xrho,mass,0.005,Reco,10,fAddMSsmearing,fAddElossGausssmearing,fAddElossLandausmearing);
    }
    if (gRandom->Rndm()<fracUnitTest) param.UnitTestDumpCorrectForMaterial(fgStreamer,crossLength*xx0,-crossLength*xrho,mass,20);
    if (status) {
        fStatusMaskMC[nPoint]|=kTrackCorrectForMaterial;
      }else{
        break;
    }
    //std::cout<<"Momentum: "<<param.GetP()<<std::endl;
    //std::cout<<"q/pt Simu: "<<param.GetParameter()[4]<<std::endl;
    fParamMC.resize(nPoint+1);
    fParamMC[nPoint]=param;
    fLayerIndex[nPoint]=indexR;
    fLoop[nPoint]=loopCounter;
    fDirection[nPoint]=direction;
    indexR+=direction;
    if (indexR>fMaxLayer) {
      fMaxLayer=indexR;
    }
    /*
    if (indexR==geom.fLayerRadius.at(geom.fLayerRadius.size()-1)) 
    {
      break;
    }
    */
    if (abs(param.GetParameter()[1])>259) break;
    if (fDecayLength>0 &&param.fLength>fDecayLength) break;   // decay particles
  }
  return 1;
}



/*

int fastParticle::simulateParticle(fastGeometry  &geom, double r[3], double p[3], int pdgCode, float maxLength, int maxPoints){
  const float kMaxSnp=0.90;
  double covar[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  fPdgCodeMC=pdgCode;
  TParticlePDG * particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
  if (particle== nullptr) {
    ::Error("fastParticle::simulateParticle","Invalid pdgCode %d",pdgCode);
    return -1;
  }
  float sign = particle->Charge()/3.;
  float mass = particle->Mass();
  AliExternalTrackParam param(r,p,covar,sign);
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  float direction=r[0]*p[0]+r[1]*p[1]+r[2]*p[2];
  direction=(direction>0)? 1.:-1.;
  if (radius==0) direction=1;
  uint indexR= uint(std::upper_bound (geom.fLayerRadius.begin(),geom.fLayerRadius.end(), radius)-geom.fLayerRadius.begin());
  int nPoint=0;
  fParamMC.resize(1);
  fParamMC[0]=param;
  fLayerIndex[0]=indexR;
  double *par = (double*)param.GetParameter();
  for (nPoint=1; nPoint<maxPoints&&length<maxLength; nPoint++){
    //printf("%d\n",nPoint);
    //param.Print();
    if (indexR>geom.fLayerRadius.size()) {
      break;
    }
    double xyz[3],pxyz[3];
    float radius  = geom.fLayerRadius[indexR];
    //float xrho    = geom.fLayerRho[indexR];
    //float xx0     = geom.fLayerX0[indexR];
    //Float_t x = param.GetXatLabR(r,localX,fBz,1);
    int status =  param.GetXYZatR(radius,geom.fBz,xyz);
    if (status==0){   // if not possible to propagate to next radius - assume looper - change direction
      float C         = param.GetC(geom.fBz);
      float R         = TMath::Abs(1/C);
      float dca       = param.GetD(0,0,geom.fBz);         // distance of closest approach to origin (0,0)
      float dla       = dca+2*R;                          // distance of longest approach
      bool  isUp      = abs(Radius-dca)>abs(Radius-dla);
      float dAlpha    = abs(TMath::ASin(param->GetSnp()))-TMath::Pi()*0.5;
      dAlpha *=(param->GetSnp()<0):-1.:1.;
      float alphaNew  = param.GetAlpha()+dAlpha;
      double paramNew[5]={par[0],par[1],par[2],par[3],par[4]};
      AliExternalTrackParam paramNew=param;
      double xyzNew[3],pxyzNew[3];
      paramNew.GetPxPyPz(pxyzNew);
      paramNew.GetXYZ(xyzNew);
      float stepDir=(direction*C*sign)>0? -1:1;
      double alphaDir  = TMath::ATan2(pxyzNew[1],pxyzNew[0]);
      if (stepDir<0) alphaDir+=TMath::Pi();
      double alpha     = TMath::ATan2(xyzNew[1],xyzNew[0]);
      float dPhi = TMath::Abs(TMath::ASin(paramNew.GetSnp()));
      float step = TMath::Cos(dPhi)*TMath::Abs(R);
      status = paramNew.Rotate(alphaDir);
      if (status==0) {
        param.Print();
        paramNew.Print();
        printf("1.) Can not rotate: \t%f\t%f\t%f\n\n",direction,C,sign);
        break;
      }

      float newX=paramNew.GetX()+stepDir*TMath::Abs(step*2);
      status = paramNew.PropagateTo(newX,geom.fBz);
      if (status==0) {
        printf("2.)\n");
        param.Print();
        paramNew.Print();
        AliExternalTrackParam paramNew2=param;
        status = paramNew2.Rotate(-alphaDir);
        float newX=paramNew2.GetX()+TMath::Abs(step*2);
        bool status2 = paramNew2.PropagateTo(newX,geom.fBz);
        paramNew2.Print();
        printf("2.) Can not propagate:\t%f\t%f\t%f\t%d\t%d\n\n\n",direction,C,sign, (direction*C*sign)>0,status2, isUp);
        break;
      }
      paramNew.GetXYZ(xyzNew);
      double alphaNew     = TMath::ATan2(xyzNew[1],xyzNew[0])+TMath::Pi();
      status = paramNew.Rotate(alphaNew);
      if (status==0) {
        printf("\n");
        param.Print();
        paramNew.Print();
        printf("3.) Can not rotate new: \t%f\t%f\t%f\t%d\n\n\n",direction,C,sign, (direction*C*sign)>0);
        break;
      }
      paramNew.SetParamOnly(-paramNew.GetX(),alphaNew-TMath::Pi(),paramNew.GetParameter());
      double *parNew = (double*)paramNew.GetParameter();
      parNew[4]*=-1; parNew[3]*=-1;
      printf("param print begin\n");
      param.Print();
      paramNew.Print();
      status = paramNew.PropagateTo(param.GetX(),geom.fBz);
      if (status==0) {
        printf("\n");
        param.Print();
        paramNew.Print();
        printf("4.) Can not propagate: \t%f\t%f\t%f\n\n",direction,C,sign);
      }
      paramNew.Print();
      param=paramNew;
      direction*=-1;
      indexR=fLayerIndex[nPoint-1];
      par = (double*)param.GetParameter();
    }else{
      double alpha  = TMath::ATan2(xyz[1],xyz[0]);
      status = param.Rotate(alpha);
      status = param.PropagateTo(radius,geom.fBz);
    }
    //
    float xrho    = geom.fLayerRho[indexR];
    float xx0     = geom.fLayerX0[indexR];
    float tanPhi2 = par[2]*par[2];
    tanPhi2=(1-tanPhi2);
    float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);               /// geometrical path assuming crossing cylinder
    param.CorrectForMeanMaterial(-crossLength*xx0,-crossLength*xrho,mass);
    fParamMC.resize(nPoint+1);
    fParamMC[nPoint]=param;
    fLayerIndex[nPoint]=indexR;
    indexR+=direction;
  }
  return 1;
}

*/

///
/// \param geom          - pointer to geometry to use
/// \param pdgCode       - pdgCode used in the reconstruction
/// \param layerStart    - starting layer to do tracking
/// \return   -  TODO  status flags to be decides
int fastParticle::reconstructParticle(fastGeometry  &geom, long pdgCode, uint layerStart){
  const Float_t chi2Cut=100;
  const float kMaxSnp=0.95;
  const float kMaxLoss=0.3;
  fLengthIn=0;
  float_t mass=0;
  fPdgCodeRec   =pdgCode;
  if (pdgCode==0){
    fMassRec=fMassMC;
    mass=fMassMC;
  }else {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
    if (particle == nullptr) {
      ::Error("fastParticle::reconstructParticle", "Invalid pdgCode %ld", pdgCode);
      return -1;
    }
    mass = particle->Mass();
    fMassRec=particle->Mass();
  }
  uint layer1 = TMath::Min(layerStart,uint(fParamMC.size()-1));
  fMaxLayerRec=layer1;
  for (;layer1>0; layer1--){
    if (fLoop[layer1]>0) continue;                                   // loop number - only closet part of helix to the production vertex
    if (TMath::Abs(fParamMC[layer1].GetSnp())>kMaxSnp) continue;     // track inclination anlge has to be smaller than kmaxSnp
    fMaxLayerRec=layer1;
    if ((fParamMC[layer1].P())>kMaxLoss*fParamMC[0].P()) break;      // if particle momneta is bigger than kMaxLoss production momenta - define starting layer
  }

  if (layer1<=3){
    //::Error("fastParticle::reconstructParticle","short track");
    return -1;
  }
  Double_t LArm=getStat(0);
  //AliExternalTrackParam4D param(fParamMC[layer1],mass,1);
  Double_t xyzS[3][3];
  Int_t step=layer1/3;
  if (step>10) step=10;
  float sign0=(fParamMC[layer1-1].GetX()>fParamMC[layer1-2].GetX())? 1.:-1.;
  Float_t alpha0=fParamMC[layer1-1].GetAlpha();
  for (int dLayer=0; dLayer<3  && layer1-step*dLayer>0; dLayer++) {
        Int_t layer=layer1-step*dLayer-1;
        Int_t layer0=layer1-1;
        //fParamMC[layer1-step*dLayer-1].GetXYZ(xyzS[dLayer]);
        xyzS[dLayer][0]=fParamMC[layer].GetX();
        xyzS[dLayer][1]=fParamMC[layer].GetY();
        xyzS[dLayer][2]=fParamMC[layer].GetZ();
        fParamMC[layer].Local2GlobalPosition(xyzS[dLayer],fParamMC[layer].GetAlpha()-alpha0);
  }
  /// seeds in alpha0 coordinate frame
  AliExternalTrackParam * paramSeedI = fastTracker::makeSeed(xyzS[0],xyzS[1],xyzS[2],0.1,0.1,geom.fBz);
  AliExternalTrackParam * paramSeed = fastTracker::makeSeedMB(xyzS[0],xyzS[1],xyzS[2],0.1,0.1,
                                                              geom.fBz,geom.fLayerX0[layer1-1],geom.fLayerRho[layer1-1],fMassMC);
  AliExternalTrackParam   paramRot(paramSeed->GetX(),alpha0, paramSeed->GetParameter(),paramSeed->GetCovariance());
  AliExternalTrackParam4D param(paramRot,mass,1);
  if (sign0<0) {
    ((double*)param.GetParameter())[4]*=-1;
    ((double*)param.GetParameter())[3]*=-1;
    ((double*)param.GetParameter())[2]*=-1;
  }
  //param.fMass=.fMass;

  Double_t dEdx=AliExternalTrackParam::BetheBlochAleph(param.P()/mass);
  //Double_t dPdx=AliExternalTrackParam4D::dPdx(fParamMC[layer1-1]);
  (*fgStreamer)<<"seedDump"<<   // seeding not ideal in case significant energy loss
    "gid="<<gid<<
    "sign0="<<sign0<<
    "fMassMC="<<fMassMC<<
    "dEdx="<<dEdx<<
    "step="<<step<<
    "seed.="<<&param<<
    "input.="<<&fParamMC[layer1-1]<<
    "input1.="<<&fParamMC[layer1-step-1]<<
    "input2.="<<&fParamMC[layer1-2*step-1]<<
    "paramSeed.="<<paramSeed<<
    "paramSeedI.="<<paramSeedI<<
    "paramRot.="<<&paramRot<<
    "\n";
  delete paramSeed;
  delete paramSeedI;
  //double *covar = (double*)param.GetCovariance();
  //for (int i=0; i<15; i++)covar[i]*=2;

//  Double_t resFactor=(geom.fLayerResolRPhi[0]*geom.fLayerResolRPhi[0]/0.01)+0.2; // this is hack - we will need to
//  double covar0[5]={0.1,0.1,(1.+2.*dEdx/param.P())/(1.+LArm),(1.+2.*dEdx/param.P())/(1.+LArm),resFactor*400*(1.+2.*dEdx/param.P())/(1.+LArm*LArm)};
//  covar[0]+=covar0[0]*covar0[0];
//  covar[2]+=covar0[1]*covar0[1];
//  covar[5]+=covar0[2]*covar0[2];
//  covar[9]+=covar0[3]*covar0[3];
//  covar[14]+=covar0[4]*covar0[4];
  //
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  fParamIn.resize(layer1+1);
  fStatusMaskIn.resize(layer1+1);
  fParamIn[layer1]=param;
  double xyz[3];
  int status=0;
  const double *par = param.GetParameter();
  for (int layer=layer1-1; layer>=0; layer--){   // dont propagate to vertex , will be done later ...
      double resol=0;
      AliExternalTrackParam & p = fParamMC[layer];
      p.GetXYZ(xyz);
      double alpha=TMath::ATan2(xyz[1],xyz[0]);
      double radius = TMath::Sqrt(xyz[0]*xyz[0]+xyz[1]*xyz[1]);
      fStatusMaskIn[layer]=0;
      if (radius>0) {
        status = param.Rotate(alpha);
      }
      if (status) {
        fStatusMaskIn[layer]|=kTrackRotate;
      }else{
        ::Error("reconstructParticle", "Rotation failed");
        break;
      }
      status = param.PropagateTo(radius,geom.fBz,1);
      if (status) {
        fStatusMaskIn[layer]|=kTrackPropagate;
      }else{
        ::Error("reconstructParticle", "Proapagation failed");
        break;
      }
      float xrho  =geom.fLayerRho[layer];
      float xx0  =geom.fLayerX0[layer];
      float deltaY = gRandom->Gaus(0,geom.fLayerResolRPhi[layer]);
      float deltaZ = gRandom->Gaus(0,geom.fLayerResolZ[layer]);
      double pos[2]={0+deltaY,xyz[2]+deltaZ};
      double cov[3]={geom.fLayerResolRPhi[layer]*geom.fLayerResolRPhi[layer],0, geom.fLayerResolZ[layer]*geom.fLayerResolZ[layer]};
      fParamIn[layer]=param;
      float chi2 =  param.GetPredictedChi2(pos, cov);
      fChi2[layer]=chi2;
      if (chi2<chi2Cut) {
        fStatusMaskIn[layer]|=kTrackChi2;
      }else{
        ::Error("reconstructParticle", "Too big chi2 %f", chi2);
        break;
      }
      if (TMath::Abs(param.GetSnp())<kMaxSnp && cov[0]>0) {
        status = param.Update(pos, cov);
        if (status) {
          fStatusMaskIn[layer]|=kTrackUpdate;
        }else{
          ::Error("reconstructParticle", "Update failed");
          break;
        }
      }

      float tanPhi2 = par[2]*par[2];
      tanPhi2/=(1-tanPhi2);
      float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);                /// geometrical path assuming crossing cylinder
      //status = param.AliExternalTrackParam::CorrectForMeanMaterial(crossLength*xx0,crossLength*xrho,mass);
      for (Int_t ic=0;ic<5; ic++) {
        status*= param.CorrectForMeanMaterial(crossLength * xx0/5., crossLength * xrho/5., mass, 0.01);
      }
      //status = param.CorrectForMeanMaterialT4(crossLength*xx0,crossLength*xrho,mass);
      if (gRandom->Rndm() <fracUnitTest) param.UnitTestDumpCorrectForMaterial(fgStreamer,crossLength*xx0,crossLength*xrho,mass,20);
      if (status) {
        fStatusMaskIn[layer]|=kTrackCorrectForMaterial;
      }else{
        ::Error("reconstructParticle", "Correct for material failed");
        break;
      }
      fLengthIn++;
  }
  return 1;
}

/// \param geom          - pointer to geometry to use
/// \param pdgCode       - pdgCode used in the reconstruction
/// \param layerStart    - starting layer to do tracking
/// \return   -  TODO  status flags to be decides
int fastParticle::reconstructParticleOptions(fastGeometry  &geom, long pdgCode, uint layerStart){
  const Float_t chi2Cut=100;
  const float kMaxSnp=0.95;
  const float kMaxLoss=0.3;
  bool Reco = true;

  fLengthIn=0;
  float_t mass=0;
  fPdgCodeRec   =pdgCode;
  if (pdgCode==0){
    fMassRec=fMassMC;
    mass=fMassMC;
  }else {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
    if (particle == nullptr) {
      ::Error("fastParticle::reconstructParticle", "Invalid pdgCode %ld", pdgCode);
      return -1;
    }
    mass = particle->Mass();
    fMassRec=particle->Mass();
  }
  uint layer1 = TMath::Min(layerStart,uint(fParamMC.size()-1));
  fMaxLayerRec=layer1;
  for (;layer1>0; layer1--){
    if (fLoop[layer1]>0) continue;                                   // loop number - only closet part of helix to the production vertex
    if (TMath::Abs(fParamMC[layer1].GetSnp())>kMaxSnp) continue;     // track inclination anlge has to be smaller than kmaxSnp
    fMaxLayerRec=layer1;
    if ((fParamMC[layer1].P())>kMaxLoss*fParamMC[0].P()) break;      // if particle momneta is bigger than kMaxLoss production momenta - define starting layer
  }

  if (layer1<=3){
    ::Error("fastParticle::reconstructParticle","short track layer1 = %d",layer1);
    return -1;
  }
  Double_t LArm=getStat(0);
  //AliExternalTrackParam4D param(fParamMC[layer1],mass,1);
  Double_t xyzS[3][3];
  Int_t step=layer1/3;
  if (step>10) step=10;
  float sign0=(fParamMC[layer1-1].GetX()>fParamMC[layer1-2].GetX())? 1.:-1.;
  Float_t alpha0=fParamMC[layer1-1].GetAlpha();
  for (int dLayer=0; dLayer<3  && layer1-step*dLayer>0; dLayer++) {
        Int_t layer=layer1-step*dLayer-1;
        Int_t layer0=layer1-1;
        //fParamMC[layer1-step*dLayer-1].GetXYZ(xyzS[dLayer]);
        xyzS[dLayer][0]=fParamMC[layer].GetX();
        xyzS[dLayer][1]=fParamMC[layer].GetY();
        xyzS[dLayer][2]=fParamMC[layer].GetZ();
        //std::cout<<"xyz local:"<<xyzS[dLayer][0]<<" "<<xyzS[dLayer][1]<<" "<<xyzS[dLayer][2]<<std::endl; 
        fParamMC[layer].Local2GlobalPosition(xyzS[dLayer],fParamMC[layer].GetAlpha()-alpha0);
        //std::cout<<"xyz global:"<<xyzS[dLayer][0]<<" "<<xyzS[dLayer][1]<<" "<<xyzS[dLayer][2]<<std::endl; 
        float deltaYseed = gRandom->Gaus(0, geom.fLayerResolRPhi[layer]);
        float deltaZseed = gRandom->Gaus(0, geom.fLayerResolZ[layer]);
        xyzS[dLayer][1] = xyzS[dLayer][1]+deltaYseed;
        xyzS[dLayer][2] = xyzS[dLayer][2]+deltaZseed;
        
        //std::cout<<"deltaYseed: "<<deltaYseed<<" deltaZseed: "<<deltaZseed<<std::endl;
       
  }
  /// seeds in alpha0 coordinate frame
  AliExternalTrackParam * paramSeedI = fastTracker::makeSeed(xyzS[0],xyzS[1],xyzS[2],geom.fLayerResolRPhi[0],geom.fLayerResolZ[0],geom.fBz);
  AliExternalTrackParam * paramSeed =  fastTracker::makeSeedMBOptions(xyzS[0],xyzS[1],xyzS[2],geom.fLayerResolRPhi[0],geom.fLayerResolZ[0], geom.fBz,geom.fLayerX0[layer1-1],geom.fLayerRho[layer1-1],fMassMC,5,fAddElossHelix,fAddMSHelix);
  
  AliExternalTrackParam paramRot(paramSeed->GetX(),alpha0, paramSeed->GetParameter(),paramSeed->GetCovariance());
  //std::cout<<"paramRoT: ";
  //for(int i=0;i<5;i++) std::cout<<paramRot.GetParameter()[i]<<" ";
  //std::cout<<" alpha: "<<paramRot.GetAlpha()<<" X: "<<paramRot.GetX();
  //std::cout<<std::endl;
  //std::cout<<"Cov: ";
  //for(int i=0;i<15;i++) std::cout<<paramRot.GetCovariance()[i]<<" ";
  //std::cout<<std::endl;
  
  AliExternalTrackParam4D param(paramRot,mass,1);
  if (sign0<0) {
    ((double*)param.GetParameter())[4]*=-1;
    ((double*)param.GetParameter())[3]*=-1;
    ((double*)param.GetParameter())[2]*=-1;

    ////Test modifications to cov matrix RCR^T
    ((double*)param.GetCovariance())[3]*=-1;
    ((double*)param.GetCovariance())[4]*=-1;
    ((double*)param.GetCovariance())[6]*=-1;
    ((double*)param.GetCovariance())[7]*=-1;
    ((double*)param.GetCovariance())[10]*=-1;
    ((double*)param.GetCovariance())[11]*=-1;
  }
  //param.fMass=.fMass;

  Double_t dEdx=AliExternalTrackParam::BetheBlochAleph(param.P()/mass);
  //Double_t dPdx=AliExternalTrackParam4D::dPdx(fParamMC[layer1-1]);
  (*fgStreamer)<<"seedDump"<<   // seeding not ideal in case significant energy loss
    "gid="<<gid<<
    "sign0="<<sign0<<
    "fMassMC="<<fMassMC<<
    "dEdx="<<dEdx<<
    "step="<<step<<
    "seed.="<<&param<<
    "input.="<<&fParamMC[layer1-1]<<
    "input1.="<<&fParamMC[layer1-step-1]<<
    "input2.="<<&fParamMC[layer1-2*step-1]<<
    "paramSeed.="<<paramSeed<<
    "paramSeedI.="<<paramSeedI<<
    "paramRot.="<<&paramRot<<
    "\n";
  delete paramSeed;
  delete paramSeedI;
  //double *covar = (double*)param.GetCovariance();
  //for (int i=0; i<15; i++)covar[i]*=2;

//  Double_t resFactor=(geom.fLayerResolRPhi[0]*geom.fLayerResolRPhi[0]/0.01)+0.2; // this is hack - we will need to
//  double covar0[5]={0.1,0.1,(1.+2.*dEdx/param.P())/(1.+LArm),(1.+2.*dEdx/param.P())/(1.+LArm),resFactor*400*(1.+2.*dEdx/param.P())/(1.+LArm*LArm)};
//  covar[0]+=covar0[0]*covar0[0];
//  covar[2]+=covar0[1]*covar0[1];
//  covar[5]+=covar0[2]*covar0[2];
//  covar[9]+=covar0[3]*covar0[3];
//  covar[14]+=covar0[4]*covar0[4];
  //
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  fParamIn.resize(layer1+1);
  fStatusMaskIn.resize(layer1+1);
  //std::cout<<"q/pt seed: "<<param.GetParameter()[4]<<std::endl;
  fParamIn[layer1]=param;
  double xyz[3];
  int status=0;
  const double *par = param.GetParameter();
  for (int layer=layer1-1; layer>0; layer--){   // dont propagate to vertex , will be done later ...
      double resol=0;
      AliExternalTrackParam & p = fParamMC[layer];
      p.GetXYZ(xyz);
      double alpha=TMath::ATan2(xyz[1],xyz[0]);
      double radius = TMath::Sqrt(xyz[0]*xyz[0]+xyz[1]*xyz[1]);
      fStatusMaskIn[layer]=0;
      if (radius>0) {
        status = param.Rotate(alpha);
      }
      if (status) {
        fStatusMaskIn[layer]|=kTrackRotate;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Rotation failed");
        break;
      }
      status = param.PropagateTo(radius,geom.fBz,1);
      if (status) {
        fStatusMaskIn[layer]|=kTrackPropagate;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Proapagation failed");
        break;
      }
      float xrho  =geom.fLayerRho[layer];
      float xx0  =geom.fLayerX0[layer];
      float deltaY = gRandom->Gaus(0,geom.fLayerResolRPhi[layer]);
      float deltaZ = gRandom->Gaus(0,geom.fLayerResolZ[layer]);
      double pos[2]={0+deltaY,xyz[2]+deltaZ};
      double cov[3]={geom.fLayerResolRPhi[layer]*geom.fLayerResolRPhi[layer],0, geom.fLayerResolZ[layer]*geom.fLayerResolZ[layer]};
      fParamIn[layer]=param;
      float chi2 =  param.GetPredictedChi2(pos, cov);
      fChi2[layer]=chi2;
      if (chi2<chi2Cut) {
        fStatusMaskIn[layer]|=kTrackChi2;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Too big chi2 %f", chi2);
        break;
      }
      if (TMath::Abs(param.GetSnp())<kAlmost1 && cov[0]>0) {
        status = param.Update(pos, cov);
        if (status) {
          fStatusMaskIn[layer]|=kTrackUpdate;
        }else{
          //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
          ::Error("reconstructParticle", "Update failed");
          break;
        }
      }
      else{
          //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
          ::Error("reconstructParticle", "Update failed");
          break;
        }

      float tanPhi2 = par[2]*par[2];
      tanPhi2/=(1-tanPhi2);
      float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);                /// geometrical path assuming crossing cylinder
      //status = param.AliExternalTrackParam::CorrectForMeanMaterial(crossLength*xx0,crossLength*xrho,mass);
      
      for (Int_t ic=0;ic<5; ic++) {
        if(fAddElossKalman) status*= param.CorrectForMeanMaterialOptions(crossLength * xx0/5., crossLength * xrho/5., mass, 0.01, Reco, geom.fLayerResolZ[layer], fAddMSKalman);
      }
      //status = param.CorrectForMeanMaterialT4(crossLength*xx0,crossLength*xrho,mass);
      if (gRandom->Rndm() <fracUnitTest) param.UnitTestDumpCorrectForMaterial(fgStreamer,crossLength*xx0,crossLength*xrho,mass,20);
      if (status) {
        fStatusMaskIn[layer]|=kTrackCorrectForMaterial;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Correct for material failed");
        break;
      }
      fLengthIn++;
      //std::cout<<"q/pt Reco: "<<param.GetParameter()[4]<<std::endl;
  }
  return 1;
}


int fastParticle::reconstructParticleOptionsFull(fastGeometry  &geom, long pdgCode, uint layerStart){
  const Float_t chi2Cut=100;
  const float kMaxSnp=0.95;
  const float kMaxLoss=0.3;
  bool Reco = true;

  fLengthIn=0;
  float_t mass=0;
  fPdgCodeRec   =pdgCode;
  if (pdgCode==0){
    fMassRec=fMassMC;
    mass=fMassMC;
  }else {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
    if (particle == nullptr) {
      ::Error("fastParticle::reconstructParticle", "Invalid pdgCode %ld", pdgCode);
      return -1;
    }
    mass = particle->Mass();
    fMassRec=particle->Mass();
  }
  uint layer1 = TMath::Min(layerStart,uint(fParamMC.size()-1));
  fMaxLayerRec=layer1;
  for (;layer1>0; layer1--){
    //if (fLoop[layer1]>0) continue;                                   // loop number - only closet part of helix to the production vertex
    if (TMath::Abs(fParamMC[layer1].GetSnp())>kMaxSnp) continue;     // track inclination anlge has to be smaller than kmaxSnp
    fMaxLayerRec=layer1;
    if ((fParamMC[layer1].P())>kMaxLoss*fParamMC[0].P()) break;      // if particle momneta is bigger than kMaxLoss production momenta - define starting layer
  }

  if (layer1<=3){
    ::Error("fastParticle::reconstructParticle","short track layer1 = %d",layer1);
    return -1;
  }
  Double_t LArm=getStat(0);
  //AliExternalTrackParam4D param(fParamMC[layer1],mass,1);
  Double_t xyzS[3][3];
  Int_t step=layer1/3;
  if (step>10) step=10;
  float sign0=(fParamMC[layer1-1].GetX()>fParamMC[layer1-2].GetX())? 1.:-1.;
  Float_t alpha0=fParamMC[layer1-1].GetAlpha();
  for (int dLayer=0; dLayer<3  && layer1-step*dLayer>0; dLayer++) {
        Int_t layer=layer1-step*dLayer-1;
        Int_t layer0=layer1-1;
        Int_t index = fLayerIndex[layer];
        //fParamMC[layer1-step*dLayer-1].GetXYZ(xyzS[dLayer]);
        xyzS[dLayer][0]=fParamMC[layer].GetX();
        xyzS[dLayer][1]=fParamMC[layer].GetY();
        xyzS[dLayer][2]=fParamMC[layer].GetZ();
        //std::cout<<"xyz local:"<<xyzS[dLayer][0]<<" "<<xyzS[dLayer][1]<<" "<<xyzS[dLayer][2]<<std::endl; 
        fParamMC[layer].Local2GlobalPosition(xyzS[dLayer],fParamMC[layer].GetAlpha()-alpha0);
        //std::cout<<"xyz global:"<<xyzS[dLayer][0]<<" "<<xyzS[dLayer][1]<<" "<<xyzS[dLayer][2]<<std::endl; 
        float deltaYseed = gRandom->Gaus(0, geom.fLayerResolRPhi[index]);
        float deltaZseed = gRandom->Gaus(0, geom.fLayerResolZ[index]);
        xyzS[dLayer][1] = xyzS[dLayer][1]+deltaYseed;
        xyzS[dLayer][2] = xyzS[dLayer][2]+deltaZseed;
        
        //std::cout<<"deltaYseed: "<<deltaYseed<<" deltaZseed: "<<deltaZseed<<std::endl;
       
  }
  /// seeds in alpha0 coordinate frame
  AliExternalTrackParam * paramSeedI = fastTracker::makeSeed(xyzS[0],xyzS[1],xyzS[2],geom.fLayerResolRPhi[0],geom.fLayerResolZ[0],geom.fBz);
  AliExternalTrackParam * paramSeed =  fastTracker::makeSeedMBOptions(xyzS[0],xyzS[1],xyzS[2],geom.fLayerResolRPhi[0],geom.fLayerResolZ[0], geom.fBz,geom.fLayerX0[layer1-1],geom.fLayerRho[layer1-1],fMassMC,5,fAddElossHelix,fAddMSHelix);
  
  AliExternalTrackParam paramRot(paramSeed->GetX(),alpha0, paramSeed->GetParameter(),paramSeed->GetCovariance());
  //std::cout<<"paramRoT: ";
  //for(int i=0;i<5;i++) std::cout<<paramRot.GetParameter()[i]<<" ";
  //std::cout<<" alpha: "<<paramRot.GetAlpha()<<" X: "<<paramRot.GetX();
  //std::cout<<std::endl;
  //std::cout<<"Cov: ";
  //for(int i=0;i<15;i++) std::cout<<paramRot.GetCovariance()[i]<<" ";
  //std::cout<<std::endl;
  
  AliExternalTrackParam4D param(paramRot,mass,1);
  if (sign0<0) {
    ((double*)param.GetParameter())[4]*=-1;
    ((double*)param.GetParameter())[3]*=-1;
    ((double*)param.GetParameter())[2]*=-1;

    ////Test modifications to cov matrix RCR^T
    ((double*)param.GetCovariance())[3]*=-1;
    ((double*)param.GetCovariance())[4]*=-1;
    ((double*)param.GetCovariance())[6]*=-1;
    ((double*)param.GetCovariance())[7]*=-1;
    ((double*)param.GetCovariance())[10]*=-1;
    ((double*)param.GetCovariance())[11]*=-1;
  }
  //param.fMass=.fMass;

  Double_t dEdx=AliExternalTrackParam::BetheBlochAleph(param.P()/mass);
  //Double_t dPdx=AliExternalTrackParam4D::dPdx(fParamMC[layer1-1]);
  (*fgStreamer)<<"seedDump"<<   // seeding not ideal in case significant energy loss
    "gid="<<gid<<
    "sign0="<<sign0<<
    "fMassMC="<<fMassMC<<
    "dEdx="<<dEdx<<
    "step="<<step<<
    "seed.="<<&param<<
    "input.="<<&fParamMC[layer1-1]<<
    "input1.="<<&fParamMC[layer1-step-1]<<
    "input2.="<<&fParamMC[layer1-2*step-1]<<
    "paramSeed.="<<paramSeed<<
    "paramSeedI.="<<paramSeedI<<
    "paramRot.="<<&paramRot<<
    "\n";
  delete paramSeed;
  delete paramSeedI;
  //double *covar = (double*)param.GetCovariance();
  //for (int i=0; i<15; i++)covar[i]*=2;

//  Double_t resFactor=(geom.fLayerResolRPhi[0]*geom.fLayerResolRPhi[0]/0.01)+0.2; // this is hack - we will need to
//  double covar0[5]={0.1,0.1,(1.+2.*dEdx/param.P())/(1.+LArm),(1.+2.*dEdx/param.P())/(1.+LArm),resFactor*400*(1.+2.*dEdx/param.P())/(1.+LArm*LArm)};
//  covar[0]+=covar0[0]*covar0[0];
//  covar[2]+=covar0[1]*covar0[1];
//  covar[5]+=covar0[2]*covar0[2];
//  covar[9]+=covar0[3]*covar0[3];
//  covar[14]+=covar0[4]*covar0[4];
  //
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  fParamIn.resize(layer1+1);
  fStatusMaskIn.resize(layer1+1);
  //std::cout<<"q/pt seed: "<<param.GetParameter()[4]<<std::endl;
  fParamIn[layer1]=param;
  double xyz[3];
  int status=0;
  const double *par = param.GetParameter();
  for (int layer=layer1-1; layer>0; layer--){   // dont propagate to vertex , will be done later ...
      double resol=0;
      AliExternalTrackParam & p = fParamMC[layer];
      p.GetXYZ(xyz);
      double alpha=TMath::ATan2(xyz[1],xyz[0]);
      double radius = TMath::Sqrt(xyz[0]*xyz[0]+xyz[1]*xyz[1]);
      fStatusMaskIn[layer]=0;
      if (radius>0) {
        status = param.Rotate(alpha);
      }
      if (status) {
        fStatusMaskIn[layer]|=kTrackRotate;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        param.Turn(geom.fBz);
        status = param.Rotate(param.GetAlpha());
        if (status) {
          fStatusMaskIn[layer]|=kTrackRotate;
        }
        else {
          ::Error("reconstructParticle", "Rotation failed");
          break;
        }
      }
      status = param.PropagateTo(radius,geom.fBz,1);
      if (status) {
        fStatusMaskIn[layer]|=kTrackPropagate;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Proapagation failed");
        break;
      }

      Int_t index = fLayerIndex[layer];
      float xrho  =geom.fLayerRho[index];
      float xx0  =geom.fLayerX0[index];
      float deltaY = gRandom->Gaus(0,geom.fLayerResolRPhi[index]);
      float deltaZ = gRandom->Gaus(0,geom.fLayerResolZ[index]);
      double pos[2]={0+deltaY,xyz[2]+deltaZ};
      double cov[3]={geom.fLayerResolRPhi[index]*geom.fLayerResolRPhi[index],0, geom.fLayerResolZ[index]*geom.fLayerResolZ[index]};
      fParamIn[layer]=param;
      float chi2 =  param.GetPredictedChi2(pos, cov);
      fChi2[layer]=chi2;
      if (chi2<chi2Cut) {
        fStatusMaskIn[layer]|=kTrackChi2;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Too big chi2 %f", chi2);
        break;
      }
      if (TMath::Abs(param.GetSnp())<kAlmost1 && cov[0]>0) {
        status = param.Update(pos, cov);
        if (status) {
          fStatusMaskIn[layer]|=kTrackUpdate;
        }else{
          //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
          ::Error("reconstructParticle", "Update failed");
          break;
        }
      }
      else{
          //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
          ::Error("reconstructParticle", "Update failed");
          break;
        }

      float tanPhi2 = par[2]*par[2];
      tanPhi2/=(1-tanPhi2);
      float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);                /// geometrical path assuming crossing cylinder
      //status = param.AliExternalTrackParam::CorrectForMeanMaterial(crossLength*xx0,crossLength*xrho,mass);
      
      for (Int_t ic=0;ic<5; ic++) {
        if(fAddElossKalman) status*= param.CorrectForMeanMaterialOptions(crossLength * xx0/5., crossLength * xrho/5., mass, 0.01, Reco, geom.fLayerResolZ[layer], fAddMSKalman);
      }
      //status = param.CorrectForMeanMaterialT4(crossLength*xx0,crossLength*xrho,mass);
      if (gRandom->Rndm() <fracUnitTest) param.UnitTestDumpCorrectForMaterial(fgStreamer,crossLength*xx0,crossLength*xrho,mass,20);
      if (status) {
        fStatusMaskIn[layer]|=kTrackCorrectForMaterial;
      }else{
        //std::cout<<"status: "<<fStatusMaskIn[layer]<<std::endl;
        ::Error("reconstructParticle", "Correct for material failed");
        break;
      }
      fLengthIn++;
      //std::cout<<"q/pt Reco: "<<param.GetParameter()[4]<<std::endl;
  }
  return 1;
}



///
/// \param geom          - pointer to geometry to use
/// \param pdgCode       - pdgCode used in the reconstruction
/// \param layerStart    - starting layer to do tracking
/// \return   -  TODO  status flags to be decides
int fastParticle::reconstructParticleRotate0(fastGeometry  &geom, long pdgCode, uint layerStart){
  const Float_t chi2Cut=16;
  const float kMaxSnp=0.95;
  const float kMaxLoss=0.3;
  //double covar0[5]={0.1,0.1,0.001,0.001,0.01};
  fLengthInRot=0;
  fPdgCodeRec   =pdgCode;
     float_t mass=0;
  if (pdgCode==0){
    fMassRec=fMassMC;
    mass=fMassMC;
  }else {
      TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(pdgCode);
      if (particle == nullptr) {
        ::Error("fastParticle::simulateParticle", "Invalid pdgCode %ld", pdgCode);
        return -1;
      }
      mass = particle->Mass();
      fMassRec=mass;
    }
  uint layer1 = TMath::Min(layerStart,uint(fParamMC.size()-1));
  fMaxLayerRec=layer1;
  for (;layer1>0; layer1--){
    if (fLoop[layer1]>0) continue;
    if (TMath::Abs(fParamMC[layer1].GetSnp())>kMaxSnp) continue;
    if ((fParamMC[layer1].P()/fParamMC[0].P())>kMaxLoss) break;
    fMaxLayerRec=layer1;
  }
  if (layer1<=3){
    //::Error("fastParticle::reconstructParticle","short track");
    return -1;
  }
  AliExternalTrackParam4D param(fParamMC[layer1],mass,1);
  Double_t dEdx=AliExternalTrackParam::BetheBlochAleph(param.P()/mass);
  double *covar = (double*)param.GetCovariance();
  Double_t LArm=getStat(0);
   Double_t resFactor=(geom.fLayerResolRPhi[0]*geom.fLayerResolRPhi[0]/0.01)+0.2; // this is hack - we will need to
  double covar0[5]={0.1,0.1,(1+2.*dEdx/param.P())/(1+LArm),(1+2.*dEdx/param.P())/(1+LArm),resFactor*20*20*(1+2.*dEdx/param.P())/(1+LArm*LArm)};
  for (int i=0; i<15; i++)covar[i]*=5;
  covar[0]+=covar0[0]*covar0[0];
  covar[2]+=covar0[1]*covar0[1];
  covar[5]+=covar0[2]*covar0[2];
  covar[9]+=covar0[3]*covar0[3];
  covar[14]+=covar0[4]*covar0[4];
  //
  Double_t sinT=TMath::Sin(param.GetAlpha());
  Double_t cosT=TMath::Cos(param.GetAlpha());
  //
  float length=0, time=0;
  float radius = sqrt(param.GetX()*param.GetX()+param.GetY()*param.GetY());
  fParamInRot.resize(layer1+1);
    fStatusMaskInRot.resize(layer1+1);
  fParamInRot[layer1]=param;
  double xyz[3];
  int status=0;
  const double *par = param.GetParameter();
  for (int layer=layer1-1; layer>=1; layer--){   // dont propagate to vertex , will be done later ...
    double resol=0;
    AliExternalTrackParam & p = fParamMC[layer];
    p.GetXYZ(xyz);
    double alpha=TMath::ATan2(xyz[1],xyz[0]);
    double radius = TMath::Sqrt(xyz[0]*xyz[0]+xyz[1]*xyz[1]);
    Double_t localX, localY;
    localX=cosT*xyz[0]+sinT*xyz[1];
    localY=-sinT*xyz[0]+cosT*xyz[1];
    fStatusMaskInRot[layer]=0;
    status = param.PropagateTo(localX,geom.fBz,1);
    if (status) {
      fStatusMaskInRot[layer]|=kTrackPropagate;
    }else{
      ::Error("reconstructParticle", "Propagation failed");
      break;
    }
    //

    float xrho  =geom.fLayerRho[layer];
    float xx0  =geom.fLayerX0[layer];
    float deltaY = gRandom->Gaus(0, geom.fLayerResolRPhi[layer]);
    float deltaZ = gRandom->Gaus(0, geom.fLayerResolZ[layer]);
    double pos[2]={localY+deltaY,xyz[2]+deltaZ};
    double cov[3]={geom.fLayerResolRPhi[layer]*geom.fLayerResolRPhi[layer],0, geom.fLayerResolZ[layer]*geom.fLayerResolZ[layer]};
    fParamInRot[layer]=param;    ///
    float chi2 =  param.GetPredictedChi2(pos, cov);
    fChi2[layer]=chi2;
    if (chi2<chi2Cut) {
      fStatusMaskInRot[layer] |= kTrackChi2;
    }else {
      ::Error("reconstructParticle", "Chi2 -  failed");
      break;
    }
    //
    if (TMath::Abs(param.GetSnp())<kMaxSnp &&cov[0]>0)  {
      status = param.Update(pos, cov);
      if (status) {
        fStatusMaskInRot[layer] |= kTrackUpdate;
      } else {
        ::Error("reconstructParticle", "Update failed");
        break;
      }
    }
    float tanPhi2 = par[2]*par[2];
    tanPhi2/=(1-tanPhi2);
    float crossLength=TMath::Sqrt(1.+tanPhi2+par[3]*par[3]);                /// geometrical path assuming crossing cylinder  = to be racalculated
    //status = param.AliExternalTrackParam::CorrectForMeanMaterial(crossLength*xx0,crossLength*xrho,mass);
    for (Int_t ic=0;ic<5; ic++) {
      status *= param.CorrectForMeanMaterial(crossLength * xx0/5., crossLength * xrho/5., mass, 0.01);
    }
    //status = param.CorrectForMeanMaterialT4(crossLength*xx0,crossLength*xrho,mass);
    if (status) {
      fStatusMaskInRot[layer] |= kTrackCorrectForMaterial;
    } else {
      ::Error("reconstructParticle", "Correct for material failed");
      break;
    }
      fLengthInRot=0;
  }
  return 1;
}

///
/// \param valueType      0 - <pt>,  1 - <1/pt> - 2 -<dEdxExp>, 3 - 1/dEdx, 4 - dEdx/p**2
/// \return
Float_t fastParticle::getMean(Int_t valueType,Float_t beginF, Float_t endF, Int_t powerType){
  Float_t valueMean=0;
  Float_t nPoints=0;
  if (beginF<0 || beginF>=1 || beginF>endF) return 0;
  if (endF<0 || endF>1) return 0;
  Int_t sizeRec = fMaxLayerRec;
  for (UInt_t i=beginF*sizeRec; i<endF*sizeRec;i++){
    Float_t value=0;
    if (valueType==0) value=fParamMC[i].Pt();
    if (valueType==1) value=1/fParamMC[i].Pt();
    if (valueType==2) value=TMath::Max(AliExternalTrackParam4D::BetheBlochAleph(fParamMC[i].GetP()/fMassMC),0.);
    if (valueType==3) value=TMath::Max(1/AliExternalTrackParam4D::BetheBlochAleph(fParamMC[i].GetP()/fMassMC),0.);
    if (valueType==4) value=TMath::Max(AliExternalTrackParam4D::BetheBlochAleph(fParamMC[i].GetP()/fMassMC),.0)/(fParamMC[i].P()*fParamMC[i].P());
    //
    if (powerType==2) value*=value;
    if (powerType==-1) value=1./value;
    valueMean+=value;
    nPoints++;
  }
  if (nPoints==0) return 0;
  return  valueMean/nPoints;
}
///
/// \param valueType      0 - LArmMC  1 - LArmIn
/// \param averageType    dummy
/// \return
Float_t fastParticle::getStat(Int_t valueType){
  Float_t valueMean=0;
  Float_t nPoints=0;
  Float_t rMin = -1;
  Float_t rMax = -1;
  Double_t vecMin[3],vecMax[3];
  if (valueType==0) {
    for (UInt_t i = 0; i < fParamMC.size(); i++) {
      Float_t x=  fParamMC[i].GetX();
      if (rMin>x || rMin<0)  rMin=x;
      if (rMax<x || rMax==0) rMax=x;
    }
    return rMax-rMin;
  }
  if (valueType==1) {
    for (UInt_t i = 0; i < fParamIn.size(); i++) {
      Float_t x=  fParamIn[i].GetX();
      if (rMin>x || rMin<0)  rMin=x;
      if (rMax<x || rMax==0) rMax=x;
    }
    return rMax-rMin;
  }
  if (valueType==2) {
    for (UInt_t i = 0; i < fParamIn.size(); i++) {
      Float_t x=  fParamIn[i].GetX();
      if (rMin>x || rMin<0)  {
        rMin=x; fParamIn[i].GetXYZ(vecMin);
      }
      if (rMax<x || rMax==0) {
        rMax=x; fParamIn[i].GetXYZ(vecMax);
      }
    }
    return TMath::Sqrt((vecMin[0]-vecMax[0])*(vecMin[0]-vecMax[0])+ (vecMin[1]-vecMax[1])*(vecMin[1]-vecMax[1]));
  }

  return 0;
}




/// set derived varaibles as alaiases to tree
/// \param tree
void fastParticle::setAliases(TTree & tree){
  tree.SetAlias("gxIn","cos(part.fParamIn[].fAlpha)*part.fParamIn[].fX");
  tree.SetAlias("gyIn","sin(part.fParamIn[].fAlpha)*part.fParamIn[].fX");
  tree.SetAlias("gxMC","cos(part.fParamMC[].fAlpha)*part.fParamMC[].fX");
  tree.SetAlias("gyMC","sin(part.fParamMC[].fAlpha)*part.fParamMC[].fX");
  tree.SetAlias("gzMC","part.fParamMC[].fP[1]");
  tree.SetAlias("rMC","part.fParamMC[].fX");
  //
  tree.SetAlias("ptMC","part.fParamMC[0].fData.Pt()");
  tree.SetAlias("ptMCL","part.fParamMC[].fData.Pt()");
  tree.SetAlias("pMC","part.fParamMC[0].fData.P()");
  tree.SetAlias("ptRec","part.fParamIn[0].fData.Pt()");
  tree.SetAlias("tglMC","part.fParamIn[0].fData.fP[3]");
  //
  //
  tree.SetAlias("layer","Iteration$");
  tree.SetAlias("c0MC","sqrt(part.fParamMC[].fC[0])");
  tree.SetAlias("c2MC","sqrt(part.fParamMC[].fC[2])");
  tree.SetAlias("c14MC","sqrt(part.fParamMC[].fC[14])");
  tree.SetAlias("c0In","sqrt(part.fParamIn[].fC[0])");
  tree.SetAlias("c2In","sqrt(part.fParamIn[].fC[2])");
  tree.SetAlias("c0InRot","sqrt(part.fParamInRot[].fC[0])");
  tree.SetAlias("c2InRot","sqrt(part.fParamInRot[].fC[2])");
  tree.SetAlias("dEdxExp","AliExternalTrackParam::BetheBlochAleph(pMC/fMassMC)");
  tree.SetAlias("dEdxExpSolidN","AliExternalTrackParam::BetheBlochSolid(pMC/fMassMC)/AliExternalTrackParam::BetheBlochSolid(4)");

  tree.SetAlias("dEdxExpSolid","AliExternalTrackParam::BetheBlochSolid(pMC/fMassMC)");
  tree.SetAlias("dEdxExpSolidL","AliExternalTrackParam::BetheBlochSolid(part.fParamMC[].fData.P()/fMassMC)");
  tree.SetAlias("dEdxExpSolidL1","AliExternalTrackParam::BetheBlochSolid(part.fParamMC[Iteration$-1].fData.P()/fMassMC)");
  tree.SetAlias("elossTPCIn","(part.fParamIn[159].fData.GetP()-part.fParamIn[7].fData.GetP())/part.fParamMC[1].fData.GetP()");
  tree.SetAlias("elossTPCMC","(part.fParamMC[159].fData.GetP()-part.fParamMC[7].fData.GetP())/part.fParamMC[1].fData.GetP()");
  //
  tree.SetAlias("sigmaY0","sqrt(part.fParamIn[1].fC[0]+0)");
  tree.SetAlias("sigmaZ0","sqrt(part.fParamIn[1].fC[2]+0)");
  tree.SetAlias("sigmaqPt0","sqrt(part.fParamIn[1].fC[14]+0)");
  //
  tree.SetAlias("sigmaY0Rot","sqrt(part.fParamInRot[1].fC[0]+0)");
  tree.SetAlias("sigmaZ0Rot","sqrt(part.fParamInRot[1].fC[2]+0)");
  tree.SetAlias("sigmaqPt0Rot","sqrt(part.fParamInRot[1].fC[14]+0)");
  // eloss aliases
  tree.SetAlias("eLossLog","log(AliExternalTrackParam::BetheBlochSolid(fParamMC[].P()/fParamMC[].fData.fMassMC)/AliExternalTrackParam::BetheBlochSolid(4))");
  //
  tree.SetAlias("c","(0+2.99792458e-2)");
  tree.SetAlias("Larm","part.getStat(0)");
  tree.SetAlias("dir1","part.fParamIn[1].GetDirectionSign()");

}

