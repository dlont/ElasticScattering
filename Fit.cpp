/**
 * @File Fit.cpp
 * 
 * @author Denys Lontkovskyi
 */
#include "code/Chi2Object.h"

#include "TROOT.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TStyle.h"
#include "TStopwatch.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include <cstdio>

#define NPARAMS 21

#include "code/DatasetPPdsdt.h"
#include "code/CompositeDataset.h"
#include "code/PPdsdt.h"
#include "code/TRangeCondition.h"
#include "code/Barppdsdt.h"
#include "code/PPdsdtTdependentPhase.h"
#include "code/WriteParametersInfo.h"

//////////////////////////////////////////GLOBAL VARIABLES///////////////////////////////////////////////
//	Path input file with hadrons CSs
//	Total cross sections
const char *Tfile_name1 = "pp_total_root_toterr.txt";

//	Differential cross sections
const char *Dfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt23_5.txt"; //
const char *Dfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt30_7.txt"; //
const char *Dfile_name3 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt44_699.txt"; //
const char *Dfile_name4 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt53_0(2).txt"; //
const char *Dfile_name5 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt62_5.txt";
const char *Dfile_name6 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\DATA_TOTEM\\pp_official_totem_data_7TeV.txt"; //

const char *_Dfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt31.txt"; //
const char *_Dfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt53.txt"; //
const char *_Dfile_name3 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt62.txt"; //
const char *_Dfile_name4 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt546.txt"; //
const char *_Dfile_name5 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt630.txt"; //
const char *_Dfile_name6 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\ds_dt\\barPP_ds_dt1800.txt";


//	Differential cross sections graphs for PP
TGraphErrors* Dgr1;
TGraphErrors* Dgr2;
TGraphErrors* Dgr3;
TGraphErrors* Dgr4;
TGraphErrors* Dgr5;
TGraphErrors* Dgr6;
TGraphErrors* DgrX;

//	Differential cross sections graphs for \bar PP
TGraphErrors* _Dgr1;
TGraphErrors* _Dgr2;
TGraphErrors* _Dgr3;
TGraphErrors* _Dgr4;
TGraphErrors* _Dgr5;
TGraphErrors* _Dgr6;

Int_t npoints; //Number of fitted points

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void SetUpPadTot(TPad* pad) {
    pad -> SetLogx();
    pad -> SetGridx();
    pad -> SetGridy();

    return;
}

void SetUpPadRho(TPad* pad) {
    pad -> SetLogx();
    //	pad -> SetGridx();
    //	pad -> SetGridy();

    return;
}

void SetUpPadDif(TPad* pad) {
    pad -> SetLeftMargin(0.2);
    pad -> SetLogy();
    pad -> SetGridx();
    pad -> SetGridy();

    return;
}

void SetUpTotalXSGraph(TGraph* graph) {
    graph -> SetMarkerStyle(25);
    graph -> SetMarkerSize(0.5);
    graph -> Draw("APE");
    graph -> GetXaxis() -> SetTitle("\\sqrt{s}   (GeV)");
    graph -> GetXaxis() -> CenterTitle(true);
    graph -> GetXaxis() -> SetTitleOffset(1.15);
    graph -> GetXaxis() -> SetLabelFont(132);
    graph -> GetXaxis() -> SetTitleFont(132);
    graph -> GetYaxis() -> SetTitle("\\sigma_{tot}   (mb)");
    graph -> GetYaxis() -> CenterTitle(true);
    graph -> GetYaxis() -> SetLabelFont(132);
    graph -> GetYaxis() -> SetTitleFont(132);

    return;
}

void SetUpRhoSGraph(TGraph* graph) {
    graph -> SetMarkerStyle(25);
    graph -> SetMarkerSize(0.7);
    graph -> Draw("APE");
    graph -> GetYaxis() -> SetRangeUser(-0.5, 0.5);
    graph -> GetXaxis() -> SetLimits(1, 2600.);
    graph -> GetXaxis() -> SetTitle("\\sqrt{s}   (GeV)");
    graph -> GetXaxis() -> CenterTitle(true);
    graph -> GetXaxis() -> SetLabelFont(132);
    graph -> GetXaxis() -> SetTitleFont(132);
    graph -> GetYaxis() -> SetTitle("\\rho");
    graph -> GetYaxis() -> CenterTitle(true);
    graph -> GetYaxis() -> SetLabelFont(132);
    graph -> GetYaxis() -> SetTitleFont(132);

    return;
}

void SetUpDiffXSGraph(TGraph* graph) {
    graph -> SetMarkerStyle(25);
    graph -> SetMarkerSize(0.5);
    graph -> Draw("APE");
    graph -> GetXaxis() -> SetTitle("-t   (GeV^{2})");
    graph -> GetXaxis() -> CenterTitle(true);
    graph -> GetXaxis() -> SetTitleOffset(1.15);
    graph -> GetXaxis() -> SetLabelFont(22);
    graph -> GetXaxis() -> SetTitleFont(22);
    graph -> GetYaxis() -> SetTitle("\\frac{d#sigma}{dt}   (mb/GeV^{2})");
    graph -> GetYaxis() -> CenterTitle(true);
    graph -> GetYaxis() -> SetLabelFont(22);
    graph -> GetYaxis() -> SetTitleFont(22);

    return;
}

void SetUpFunc(TF1* function, Int_t color = kRed) {
    function -> SetTitle();
    function -> SetNpx(1000);
    function -> SetLineColor(color);
    function -> SetLineWidth(2.5);

    return;
}

void PutEnergy(Double_t x1, Double_t y1, Double_t ene) {
    TString str;
    str += ene;
    str += " GeV";
    TLatex * tex = new TLatex(x1, y1, str.Data());
    tex->SetTextFont(132);
    tex->SetTextSize(0.095);
    tex->SetLineWidth(2);
    tex->Draw();

    return;
}

void Fit() {
    
    gROOT->SetStyle("Pub");
    gStyle->SetOptTitle(kFALSE);

    ////////////////////////////////////////////DIFFERENTIAL PP////////////////////////////////////
    TCanvas* theCanvasD = new TCanvas("CanvasD", "PP differential cross sections", 30, 30, 600, 600);
    theCanvasD -> Divide(3, 2);
    //theCanvasD -> SetGrayscale();	

    SetUpPadDif((TPad*) theCanvasD -> GetPad(1));
    theCanvasD -> cd(1);
    Dgr1 = new TGraphErrors(Dfile_name1, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr1);

    SetUpPadDif((TPad*) theCanvasD -> GetPad(2));
    theCanvasD -> cd(2);
    Dgr2 = new TGraphErrors(Dfile_name2, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr2);

    SetUpPadDif((TPad*) theCanvasD -> GetPad(3));
    theCanvasD -> cd(3);
    Dgr3 = new TGraphErrors(Dfile_name3, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr3);

    SetUpPadDif((TPad*) theCanvasD -> GetPad(4));
    theCanvasD -> cd(4);
    Dgr4 = new TGraphErrors(Dfile_name4, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr4);

    SetUpPadDif((TPad*) theCanvasD -> GetPad(5));
    theCanvasD -> cd(5);
    Dgr5 = new TGraphErrors(Dfile_name5, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr5);

    SetUpPadDif((TPad*) theCanvasD -> GetPad(6));
    theCanvasD -> cd(6);
    Dgr6 = new TGraphErrors(Dfile_name6, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr6);

    theCanvasD -> Modified();
    theCanvasD -> Update();

    ////////////////////////////////////////////DIFFERENTIAL BAR PP////////////////////////////////////
    TCanvas* theCanvasD_ = new TCanvas("CanvasD_", "PPbar differential cross sections", 650, 30, 600, 600);
    theCanvasD_ -> Divide(3, 2);
    //theCanvasD_ -> SetGrayscale();
    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(1));
    theCanvasD_ -> cd(1);
    _Dgr1 = new TGraphErrors(_Dfile_name1, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr1);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(2));
    theCanvasD_ -> cd(2);
    _Dgr2 = new TGraphErrors(_Dfile_name2, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr2);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(3));
    theCanvasD_ -> cd(3);
    _Dgr3 = new TGraphErrors(_Dfile_name3, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr3);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(3));
    theCanvasD_ -> cd(3);
    _Dgr3 = new TGraphErrors(_Dfile_name3, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr3);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(4));
    theCanvasD_ -> cd(4);
    _Dgr4 = new TGraphErrors(_Dfile_name4, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr4);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(5));
    theCanvasD_ -> cd(5);
    _Dgr5 = new TGraphErrors(_Dfile_name5, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr5);

    SetUpPadDif((TPad*) theCanvasD_ -> GetPad(6));
    theCanvasD_ -> cd(6);
    _Dgr6 = new TGraphErrors(_Dfile_name6, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr6);

    theCanvasD_ -> Modified();
    theCanvasD_ -> Update();

    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 6.);
//    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.8, 6.);
//    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 2.5, 6.);
//    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 0.8);
//    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.5, 1.);
//    condTinRange->print();
    TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 5.5);
//    TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 0.8, 5.5);
//    TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 2.5, 5.5);
//    TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 0.8);
//    TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 0.5, 1.);
//    condTinRange1->print();

    TRangeCondition* condTinRange2 = new TRangeCondition("ConditionTinRange0.1-8", 0.3, 3.5);
//    condTinRange2->print();
    
    double s = 23.503*23.503;
    DatasetPPdsdt* ppdsdt23 = new DatasetPPdsdt( "dsdtPP23GeV", s );
    ppdsdt23->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt23->setGraph( Dgr1 );
    ppdsdt23->setCondition( condTinRange );
    
    s = 30.7*30.7;
    DatasetPPdsdt* ppdsdt30 = new DatasetPPdsdt( "dsdtPP30GeV", s );
    ppdsdt30->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt30->setGraph( Dgr2 );
    ppdsdt30->setCondition( condTinRange );
    
    s = 44.699*44.699;
    DatasetPPdsdt* ppdsdt44 = new DatasetPPdsdt( "dsdtPP44GeV", s );
    ppdsdt44->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt44->setGraph( Dgr3 );
    ppdsdt44->setCondition( condTinRange );
  
    s = 53.0*53.0;
    DatasetPPdsdt* ppdsdt53 = new DatasetPPdsdt( "dsdtPP53GeV", s );
    ppdsdt53->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt53->setGraph( Dgr4 );
    ppdsdt53->setCondition( condTinRange );
    
    s = 62.5*62.5;
    DatasetPPdsdt* ppdsdt62 = new DatasetPPdsdt( "dsdtPP63GeV", s );
    ppdsdt62->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt62->setGraph( Dgr5 );
    ppdsdt62->setCondition( condTinRange1 );
    
    s = 7000.*7000.;
    DatasetPPdsdt* ppdsdt7000 = new DatasetPPdsdt( "dsdtPP7000GeV", s );
    ppdsdt7000->setModel( new PPdsdtTdependentPhase(s) );
    ppdsdt7000->setGraph( Dgr6 );
    ppdsdt7000->setCondition( condTinRange2 );
    
    CompositeDataset* dataset_dsdtPP = new CompositeDataset( "dsdtPPcombined" );
//    dataset_dsdtPP->getComposite()->addDataset( ppdsdt23 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt30 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt44 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt53 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt62 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt7000 );
//    dataset_dsdtPP->print();
    
    Chi2Object chi2;
    chi2._useDifferentialCS = true;
    chi2.setDataSetsDSigmaDtPP( dataset_dsdtPP );
    
    const Int_t nTries = 1;
    const Double_t scale = 0.1;
    Double_t minChi2 = 1e100;
    Double_t minPar[NPARAMS], minParErr[NPARAMS];

    //	Fitting with Minuit
    //  ROOT::Minuit2::Minuit2Minimizer min( "Migrad" );
    //  Migrad, Simplex, Combined, Scan, Fumili

    //  Fitting with simulated anealing
    //  ROOT::Math::GSLSimAnMinimizer min;

    //  Fitting with Marquardt-Levenberg algorithm
    //  ROOT::Math::GSLNLSMinimizer min;

    // Fitting with GSL
    // ROOT::Math::GSLMinimizer min( ROOT::Math::kVectorBFGS2 );
    // kConjugateFR, kConjugatePR, kVectorBFGS,
    // kVectorBFGS2, kSteepestDescent
//    ROOT::Math::GSLMinimizer* min = new ROOT::Math::GSLMinimizer( ROOT::Math::kSteepestDescent );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "GSLSimAn", "" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "GSLMultiFit", "" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "GSLMultiMin", "ConjugatePR" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "GSLMultiMin", "ConjugateFR" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "GSLMultiMin", "BFGS2" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "Fumili", "" );
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "Minuit2", "Fumili2" );
    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

    min->SetPrintLevel(2);
    min->SetMaxFunctionCalls(1000000);
    min->SetMaxIterations(1e3);
//    min->SetTolerance(1e-15);
//    min->SetTolerance(100);
//    min->SetPrecision(1e-15);
    ROOT::Math::Functor f(chi2, NPARAMS);
    min->SetFunction(f);

    #include "parameters/best_f_soft_hard.par"
    
    //	Secondary reggeons
    min->SetVariable(0, ipar[0].first, ipar[0].second, 0.01);     min->SetFixedVariable(0, ipar[0].first, ipar[0].second);
    min->SetVariable(1, ipar[1].first, ipar[1].second, 0.01);     min->SetFixedVariable(1, ipar[1].first, ipar[1].second);
    min->SetVariable(2, ipar[2].first, ipar[2].second, 0.01);     min->SetFixedVariable(2, ipar[2].first, ipar[2].second);
    min->SetVariable(3, ipar[3].first, ipar[3].second, 0.01);     min->SetFixedVariable(3, ipar[3].first, ipar[3].second);
    min->SetVariable(4, ipar[4].first, ipar[4].second, 0.01);     //min->SetFixedVariable(4, ipar[4].first, ipar[4].second);
    min->SetVariable(5, ipar[5].first, ipar[5].second, 0.01);     //min->SetFixedVariable(5, ipar[5].first, ipar[5].second);
    min->SetVariable(6, ipar[6].first, ipar[6].second, 0.01);     //min->SetFixedVariable(6, ipar[6].first, ipar[6].second);
    min->SetVariable(7, ipar[7].first, ipar[7].second, 0.01);     //min->SetFixedVariable(7, ipar[7].first, ipar[7].second);
    ////	Primary reggeons (Pomeron)    
    min->SetVariable(8, ipar[8].first, ipar[8].second, 0.01);       min->SetFixedVariable(8, ipar[8].first, ipar[8].second );
    min->SetVariable(9, ipar[9].first, ipar[9].second, 0.01);       //min->SetFixedVariable(9, ipar[9].first, ipar[9].second );
    min->SetVariable(10, ipar[10].first, ipar[10].second, 0.01);    //min->SetFixedVariable(10, ipar[10].first, ipar[10].second);
    min->SetVariable(11, ipar[11].first, ipar[11].second, 0.01);    //min->SetFixedVariable(11, ipar[11].first, ipar[11].second);
        
    min->SetVariable(12, ipar[12].first, ipar[12].second, 0.01);    //min->SetFixedVariable(12, ipar[12].first, ipar[12].second);
    min->SetVariable(13, ipar[13].first, ipar[13].second, 0.01);    //min->SetFixedVariable(13, ipar[13].first, ipar[13].second);
    min->SetVariable(14, ipar[14].first, ipar[14].second, 0.01);    //min->SetFixedVariable(14, ipar[14].first, ipar[14].second);
    min->SetVariable(15, ipar[15].first, ipar[15].second, 0.01);    //min->SetFixedVariable(15, ipar[15].first, ipar[15].second);
        
    min->SetVariable(16, ipar[16].first, ipar[16].second, 0.01);    min->SetFixedVariable(16, ipar[16].first, ipar[16].second );
    min->SetVariable(17, ipar[17].first, ipar[17].second, 0.01);    //min->SetFixedVariable(17, ipar[17].first, ipar[17].second );
    min->SetVariable(18, ipar[18].first, ipar[18].second, 0.01);    //min->SetFixedVariable(18, ipar[18].first, ipar[18].second );
    min->SetVariable(19, ipar[19].first, ipar[19].second, 0.01);    //min->SetFixedVariable(19, ipar[19].first, ipar[19].second );
    min->SetVariable(20, ipar[20].first, ipar[20].second, 0.01);    //min->SetFixedVariable(20, ipar[20].first, ipar[20].second );

    TStopwatch timer;
    printf("Starting timer\n");
    timer.Start();
    
    min->Minimize();

    npoints = chi2.getNPoints();
    printf("Number of fitted points= %d\n", npoints);

    const Double_t *par, *parErr;
    par = min->X();
    parErr = min->Errors();
    Int_t NfreeParam = min->NFree();
    Double_t NDF = (npoints - NfreeParam);
    minChi2 = min->MinValue();
    memcpy(minPar, par, NPARAMS * sizeof (Double_t));
    memcpy(minParErr, parErr, NPARAMS * sizeof (Double_t));
    printf("Chi2/ndf= %f/%f= %f\n", min->MinValue(), NDF, min->MinValue() / NDF);

    Int_t color = kRed;

    ////////////////////////////////////////////DIFFERENTIAL PP////////////////////////////////////
    theCanvasD -> cd(1);
    Functor* f23 = ppdsdt23->getModel();
    TF1* Dfunction1 = new TF1("Dfunction1", f23, 0., 7., NPARAMS);
    Dfunction1 -> SetParameters(par);
    SetUpFunc(Dfunction1, color);
    Dfunction1 -> Draw("same");
    PutEnergy(3., 1.e-2, 23.5);
    //cout.precision(10); cout << "diff: " << Dfunction1->Eval(10) << endl;

    theCanvasD -> cd(2);
    Functor* f30 = ppdsdt30->getModel();
    TF1* Dfunction2 = new TF1("Dfunction2", f30, 0., 7., NPARAMS);
    Dfunction2 -> SetParameters(par);
    SetUpFunc(Dfunction2, color);
    Dfunction2 -> Draw("same");
    PutEnergy(3., 1.e-2, 31.);

    theCanvasD -> cd(3);
    Functor* f44 = ppdsdt44->getModel();
    TF1* Dfunction3 = new TF1("Dfunction3", f44, 0., 10., NPARAMS);
    Dfunction3 -> SetParameters(par);
    SetUpFunc(Dfunction3, color);
    Dfunction3 -> Draw("same");
    PutEnergy(2., 1.e-2, 45.);

    theCanvasD -> cd(4);
    Functor* f53 = ppdsdt53->getModel();
    TF1* Dfunction4 = new TF1("Dfunction4", f53, 0., 7., NPARAMS);
    Dfunction4 -> SetParameters(par);
    SetUpFunc(Dfunction4, color);
    Dfunction4 -> Draw("same");
    PutEnergy(3., 1.e-2, 53.);

    theCanvasD -> cd(5);
    Functor* f62 = ppdsdt62->getModel();
    TF1* Dfunction5 = new TF1("Dfunction5", f62, 0., 7., NPARAMS);
    Dfunction5 -> SetParameters(par);
    SetUpFunc(Dfunction5, color);
    Dfunction5 -> Draw("same");
    PutEnergy(3., 1.e-2, 62.5);

    theCanvasD -> cd(6);
    Functor* f7000 = ppdsdt7000->getModel();
    TF1* Dfunction6 = new TF1("Dfunction6", f7000, 0., 7., NPARAMS + 1);
    Dfunction6 -> SetParameters(par);
    SetUpFunc(Dfunction6, color);
    Dfunction6 -> Draw("same");
    PutEnergy(1.5, 1.e-2, 7000.);
    
    ////////////////////////////////////////////DIFFERENTIAL BAR PP////////////////////////////////////
    theCanvasD_ -> cd(1);
    Functor* f31ppb = new BarPPdsdt(31. * 31.);
    TF1* _Dfunction1 = new TF1("_Dfunction1", f31ppb, 0., 7., NPARAMS);
    _Dfunction1 -> SetParameters(par);
    SetUpFunc(_Dfunction1, color);
    _Dfunction1 -> Draw("same");
    PutEnergy(0.6, 1., 31.);

    theCanvasD_ -> cd(2);
    Functor* f53ppb = new BarPPdsdt(53. * 53.);
    TF1* _Dfunction2 = new TF1("_Dfunction2", f53ppb, 0., 7., NPARAMS);
    _Dfunction2 -> SetParameters(par);
    SetUpFunc(_Dfunction2, color);
    _Dfunction2 -> Draw("same");
    PutEnergy(2., 1.e-2, 53.);

    theCanvasD_ -> cd(3);
    Functor* f62ppb = new BarPPdsdt(62. * 62.);
    TF1* _Dfunction3 = new TF1("_Dfunction3", f62ppb, 0., 7., NPARAMS);
    _Dfunction3 -> SetParameters(par);
    SetUpFunc(_Dfunction3, color);
    _Dfunction3 -> Draw("same");
    PutEnergy(0.6, 1., 62.);

    theCanvasD_ -> cd(4);
    Functor* f546ppb = new BarPPdsdt(546. * 546.);
    TF1* _Dfunction4 = new TF1("_Dfunction4", f546ppb, 0., 7., NPARAMS);
    _Dfunction4 -> SetParameters(par);
    SetUpFunc(_Dfunction4, color);
    _Dfunction4 -> Draw("same");
    PutEnergy(0.6, 1., 546.);

    theCanvasD_ -> cd(5);
    Functor* f630ppb = new BarPPdsdt(630. * 630.);
    TF1* _Dfunction5 = new TF1("_Dfunction5", f630ppb, 0., 7., NPARAMS);
    _Dfunction5 -> SetParameters(par);
    SetUpFunc(_Dfunction5, color);
    _Dfunction5 -> Draw("same");
    PutEnergy(1.6, 1.e-3, 630.);

    theCanvasD_ -> cd(6);
    Functor* f1800ppb = new BarPPdsdt(1800. * 1800.);
    TF1* _Dfunction6 = new TF1("_Dfunction6", f1800ppb, 0., 7., NPARAMS);
    _Dfunction6 -> SetParameters(par);
    SetUpFunc(_Dfunction6, color);
    _Dfunction6 -> Draw("same");
    PutEnergy(0.4, 10., 1800.);

    ///////////////////////// 7TEV TOTEM ///////////////////////////////
    TCanvas* theCanvasTOTEM = new TCanvas("CanvasTOTEM", "PP differential cross sections", 500, 30, 600, 600);
    theCanvasTOTEM -> cd();
    theCanvasTOTEM -> SetLeftMargin(0.2);
    theCanvasTOTEM -> SetLogy(kTRUE);
    SetUpDiffXSGraph(Dgr6);
    Dfunction6 ->SetLineWidth(3);
    Dfunction6 -> Draw("same");
    PutEnergy(4., 1.e-2, 7000);

    theCanvasTOTEM -> Modified();
    //theCanvasTOTEM -> Print("plots\\separate_fit_each_energy\\7000GeV.eps");

    WriteParametersInfo* dropper = new WriteParametersInfo();
    int ids[] = {8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::vector<int> parIDs(ids, ids + sizeof (ids) / sizeof (int));
    dropper->setMinimizer(min);
    dropper->DumpFileCSV( npoints, "XXX.csv", parIDs );
    dropper->DumpInitParametersInclude( "XXX.par" );
//
//        str_postfix = "PP_";
//        str_postfix += strEne;
//        str_postfix += ".arr";
//        TString file1name(TString() + str_postfix);
//        ofstream file1(file1name.Data());
//        file1 << "Double_t Dpar[" << NPARAMS << "] = { " << std::endl;
//        for (int k = 0; k < NPARAMS - 1; k++) file1 << minPar[k] << ", " << std::endl;
//        file1 << minPar[NPARAMS - 1] << "};" << std::endl;
//        file1.close();
//


    timer.Stop();
    printf("Time at the end of job = %f seconds\n", timer.CpuTime());

    return;
}
