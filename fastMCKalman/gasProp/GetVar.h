#ifndef _GETVAR_
#define _GETVAR_

#include "stdio.h"
//#include "TAxis.h"
#include "TFile.h"
//#include "TCanvas.h"
//#include "TColor.h"
//#include "TGraph.h"
//#include "TGraphErrors.h"
//#include "TGraphAsymmErrors.h"
//#include "TLegend.h"
//#include "TLine.h"
//#include "TList.h"
#include "TH1I.h"
#include "TSystem.h"
#include "TTree.h"
#include "GasUtils.h"
#include "gasElement.h"
#include "gasMixer.h"
//#include "/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/AliRoot/STAT/AliNDLocalRegression.h"
#include "AliNDLocalRegression.h"
#include "TVector.h"
//#include "~/Documents/Universita/Federico_2020-2021/Aliwork/AliRoot/STAT/AliNDLocalRegression.h"
//#include "GetVar.h"

//using namespace GasUtils;
#pragma link C++ class map<int,TVectorF>+;
#include <map>
namespace GetVar //fquencher in percentage, p in mBar2
{
  extern TTree * tree;
  extern  std::map<std::string,AliNDLocalRegression*> mapRegressionDtStr;
  extern  std::map<int,TString> mapId;
  extern  std::map<int,TVectorF> mapParam;
  extern  std::map<int,AliNDLocalRegression*> mapRegressionDtInt;

  

  bool Init();
  bool CreateOrganicCompound(gasMixer & gQuencher, int nC, int nH, int nF, gasMixer gC, gasMixer gH, gasMixer gF);
  //float GetDensity(int fquencher=10, int p=1000, int nC=1, int nH=4, int Zgas=18, int Agas=40){return 0;}  //TODO
  float GetSigmaT(int fquencher=10, int p=1000, int nC=1, int nH=4, int Zgas=18, int Agas=40, int E=165, int B=0); // diffusion in transverse plane reults in microm/sqrt(cm)
  float GetSigmaTErr(int fquencher=10, int p=1000, int nC=1, int nH=4, int Zgas=18, int Agas=40, int E=165, int B=0);
  float GetX0Rel(int fquencher=10, int p=1000 , int nC=1, int nH=4, int Zgas=18, int Agas=40); //fquencher in percentage, p in mBar2, result in g/cm^2  (density x length)
  float GetDensity(int fquencher=10, int p=1000 , int nC=1, int nH=4, int Zgas=18, int Agas=40); //g/cm^3
  float GetNumberOfX0(int fquencher=10, int p=1000 , int nC=1, int nH=4, int Zgas=18, int Agas=40, float length=0); //TODO //fquencher in percentage, p in mBar2, result number of rad lengths
  float GetX0(int fquencher=10, int p=1000 , int nC=1, int nH=4, int Zgas=18, int Agas=40); //TODO //fquencher in percentage, p in mBar2, result radiation length in cm
  float GetX0F(int fquencher, int p , int nC, int nH, int nF, int Zgas, int Agas, int mC, int mH, int mF);
  // interpolation using local regression
  //float GetSigmaT(int fquencher=10, int p=1000, int nC=1, int nH=4, int Zgas=18, int Agas=40, int E=165, int B=0) {return 0;}// TODO// diffusion in transverse plane reults in microm/sqrt(cm)

  
  double getDtNorm(int id,  float fquencher, float ep);
  char * getIdName(int id);
  
  void makeGasFunction(int minEntries, const char* output=0);
  
  void initTree();
  
}

#endif