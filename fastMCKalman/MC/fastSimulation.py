#from ROOT import gROOT, AliDrawStyle, gStyle
import ROOT
from ROOT import gROOT, gStyle,gSystem

gSystem.Load("$fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/AliExternalTrackParam.so");
gROOT.LoadMacro("$fastMCKalmanOptTesting/fastMCKalman/MC//fastSimulation.cxx+")
gROOT.LoadMacro("$fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulationTest.C")
#AliDrawStyle.SetDefaults()
#AliDrawStyle.ApplyStyle("figTemplate")
#gStyle.SetOptTitle(1)


def setAliasesFast(tree):
    print("set aliases")
    tree.SetAlias("gxIn","cos(part.fParamIn[].fAlpha)*part.fParamIn[].fX")
    tree.SetAlias("gyIn","sin(part.fParamIn[].fAlpha)*part.fParamIn[].fX")
    tree.SetAlias("gxMC","cos(part.fParamMC[].fAlpha)*part.fParamMC[].fX")
    tree.SetAlias("gyMC","sin(part.fParamMC[].fAlpha)*part.fParamMC[].fX")
    tree.SetAlias("ptMC","part.fParamMC[0].fData.Pt()")
    tree.SetAlias("ptIn","part.fParamIn[1].fData.Pt()")
    tree.SetAlias("tglMC","part.fParamMC[0].fData.Tgl()")
    tree.SetAlias("tglIn","part.fParamIn[1].fData.Tgl()")
    #tree.SetAlias
