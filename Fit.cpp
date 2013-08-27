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

#define NPARAMS 20

#include "SigDig.cxx"

#include "code/DatasetPPdsdt.h"
#include "code/CompositeDataset.h"
#include "code/PPdsdt.h"
#include "code/TRangeCondition.h"
#include "code/Barppdsdt.h"

//////////////////////////////////////////GLOBAL VARIABLES///////////////////////////////////////////////
//	Path input file with hadrons CSs
//	Total cross sections
const char *Tfile_name1 = "pp_total_root_toterr.txt";

//	Differential cross sections
const char *Dfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt23_5.txt"; //
const char *Dfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt30_7.txt"; //
//const char *Dfile_name3 = "PP_ds_dt53_0.txt"; //
const char *Dfile_name3 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt53_0(2).txt"; //
//const char *Dfile_name3 = "PP_ds_dt52_8.txt";
const char *Dfile_name4 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt62_5.txt"; //
//const char *Dfile_name5 = "PP_ds_dt27_4.txt";
//const char *Dfile_name5 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\pp_totem_data_Tamasz.txt";
const char *Dfile_name5 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\DATA_TOTEM\\pp_official_totem_data_7TeV.txt";
const char *Dfile_name6 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\BPv003\\PP_ds_dt44_699.txt"; //

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

    TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 8.);
//    condTinRange->print();

    DatasetPPdsdt* ppdsdt23 = new DatasetPPdsdt( "dsdtPP23GeV", 23.503*23.503 );
    ppdsdt23->setGraph( Dgr1 );
    ppdsdt23->setCondition( condTinRange );
    
    DatasetPPdsdt* ppdsdt30 = new DatasetPPdsdt( "dsdtPP30GeV", 30.7*30.7 );
    ppdsdt30->setGraph( Dgr2 );
    ppdsdt30->setCondition( condTinRange );
    
    DatasetPPdsdt* ppdsdt53 = new DatasetPPdsdt( "dsdtPP53GeV", 53.0*53.0 );
    ppdsdt53->setGraph( Dgr3 );
    ppdsdt53->setCondition( condTinRange );
    
    DatasetPPdsdt* ppdsdt62 = new DatasetPPdsdt( "dsdtPP63GeV", 62.5*62.5 );
    ppdsdt62->setGraph( Dgr4 );
    ppdsdt62->setCondition( condTinRange );
    
    DatasetPPdsdt* ppdsdt44 = new DatasetPPdsdt( "dsdtPP44GeV", 44.699*44.699 );
    ppdsdt44->setGraph( Dgr6 );
    ppdsdt44->setCondition( condTinRange );
    
    CompositeDataset* dataset_dsdtPP = new CompositeDataset( "dsdtPPcombined" );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt23 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt30 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt44 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt53 );
    dataset_dsdtPP->getComposite()->addDataset( ppdsdt62 );
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
//    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer( "Minuit2", "Fumili2" );
    ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

    min->SetPrintLevel(2);
    min->SetMaxFunctionCalls(1000000);
    min->SetMaxIterations(1e5);
    min->SetTolerance(1e-15);
    min->SetPrecision(1e-15);
    //min->SetTolerance(100);
    ROOT::Math::Functor f(chi2, NPARAMS);
    min->SetFunction(f);

    TStopwatch timer;
    printf("Starting timer\n");
    timer.Start();


    const Double_t Pi = TMath::Pi();
    ///////////////////////////////////////linear trajectory parameters
    const Double_t a_w = 0.;
    const Double_t b_w = 0.;
    const Double_t alpha_w0 = 0.; //w Regge tr. intercept
    const Double_t alpha_w = 0.; //w Regge tr. slope
    //	f-Reggeon parameters
    const Double_t a_f = 0.;
    const Double_t b_f = 0.;
    const Double_t alpha_f0 = 0.; //f Regge tr. intercept
    const Double_t alpha_f = 0.; //f Regge tr. slope
    //Barger Phillips
    //const Double_t a_p = 17963.;			
    //const Double_t b_p = 10.2097;			
    //const Double_t c_p = 77.3003;			
    //const Double_t d_p = 0.0508336;		
    //const Double_t phi1_p = 1.60039;		
    //const Double_t phi2_p = -1.01501;		
    ////CREMEA FIT PPbar chi2/ndf=1.95	(0.35%TOTEM err)
    const Double_t a = 13.1269;
    const Double_t b1 = 1.38992;
    const Double_t b2 = 0.; //attention: for pure linear pomeron trajectory
    //const Double_t b2 	= 0.01;		//attention: for linear + sqrt brake trajectory
    const Double_t c = 3628.43;
    const Double_t d1 = 9.41059;
    const Double_t d2 = 0.; //attention: for pure linear pomeron trajectory
    //const Double_t d2 	= 0.01;		//attention: for linear + sqrt brake trajectory
    const Double_t eps1 = 0.;
    const Double_t eps2 = 0.;
    const Double_t phi = 2.82675;

    const Double_t a_o = 1.0; //attention: S0r parameter 
    const Double_t c_o = 0.0;
    const Double_t phi2_o = 0.0;


    //	Secondary reggeons
    min->SetVariable(0, "a_w", a_w, 0.01);                  min->SetFixedVariable(0, "a_w", a_w);
    min->SetVariable(1, "alpha_w0", alpha_w0, 0.01);        min->SetFixedVariable(1, "alpha_w0", alpha_w0);
    min->SetVariable(2, "alpha_w", alpha_w, 0.01);          min->SetFixedVariable(2, "alpha_w", alpha_w);
    min->SetVariable(3, "b_w", b_w, 0.01);                  min->SetFixedVariable(3, "b_w", b_w);
    min->SetVariable(4, "a_f", a_f, 0.01);                  min->SetFixedVariable(4, "a_f", a_f);
    min->SetVariable(5, "alpha_f0", alpha_f0, 0.01);        min->SetFixedVariable(5, "alpha_f0", alpha_f0);
    min->SetVariable(6, "alpha_f", alpha_f, 0.01);          min->SetFixedVariable(6, "alpha_f", alpha_f);
    min->SetVariable(7, "b_f", b_f, 0.01);                  min->SetFixedVariable(7, "b_f", b_f);
    ////	Primary reggeons (Pomeron)
    min->SetVariable(8, "\\sqrt A", a, 0.01);               //min->SetFixedVariable(8, "\\sqrt A",			a );
    min->SetVariable(9, "B_1", b1, 0.01);                   //min->SetFixedVariable(9, "B_1",		b1 );
    min->SetVariable(10, "B_2", b2, 0.01);                  min->SetFixedVariable(10, "B_2", b2);
    min->SetVariable(11, "\\sqrt C", c, 0.01);              //min->SetFixedVariable(11, "\\sqrt C",		c);
    min->SetVariable(12, "D_1", d1, 0.01);                  //min->SetFixedVariable(12, "D_1", 		d1 );
    min->SetVariable(13, "D_2", d2, 0.01);                  min->SetFixedVariable(13, "D_2", d2);
    min->SetVariable(14, "\\varepsilon_1", eps1, 0.01);     min->SetFixedVariable(14, "\\varepsilon_1", eps1);
    min->SetVariable(15, "\\varepsilon_2", eps2, 0.01);     min->SetFixedVariable(15, "\\varepsilon_2", eps2);
    min->SetVariable(16, "\\varphi", 2.7, 0.01);            //min->SetFixedVariable(16, "\\varphi",	phi );
    
    min->SetVariable(17, "a_o", a_o, 0.01);                 min->SetFixedVariable(17, "a_o", a_o);
    min->SetVariable(18, "c_o", c_o, 0.01);                 min->SetFixedVariable(18, "c_o", c_o);
    min->SetVariable(19, "phi2_o", phi2_o, 0.01);           min->SetFixedVariable(19, "phi2_o", phi2_o);

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
    //cout.precision(10); cout << "diff: " << Dfunction1->Eval(10) << endl;
    PutEnergy(3., 1.e-2, 23.5);

    theCanvasD -> cd(2);
    Functor* f30 = ppdsdt30->getModel();
    TF1* Dfunction2 = new TF1("Dfunction2", f30, 0., 7., NPARAMS);
    Dfunction2 -> SetParameters(par);
    SetUpFunc(Dfunction2, color);
    Dfunction2 -> Draw("same");
    PutEnergy(3., 1.e-2, 31.);

    theCanvasD -> cd(3);
    Functor* f53 = ppdsdt53->getModel();
    TF1* Dfunction3 = new TF1("Dfunction3", f53, 0., 10., NPARAMS);
    Dfunction3 -> SetParameters(par);
    SetUpFunc(Dfunction3, color);
    Dfunction3 -> Draw("same");
    PutEnergy(2., 1.e-2, 53.);

    theCanvasD -> cd(4);
    Functor* f62 = ppdsdt62->getModel();
    TF1* Dfunction4 = new TF1("Dfunction4", f62, 0., 7., NPARAMS);
    Dfunction4 -> SetParameters(par);
    SetUpFunc(Dfunction4, color);
    Dfunction4 -> Draw("same");
    PutEnergy(3., 1.e-2, 62.5);

    theCanvasD -> cd(5);
//    TF1* Dfunction5 = new TF1("Dfunction5", GRAPHFunctionPPCS_dt, 0., 7., NPARAMS + 1);
//    Dfunction5 -> SetParameters(par);
//    SetUpFunc(Dfunction5, color);
//    Dfunction5 -> Draw("same");
//    PutEnergy(1.5, 1.e-2, 7000.);

    theCanvasD -> cd(6);
    Functor* f44 = ppdsdt44->getModel();
    TF1* Dfunction6 = new TF1("Dfunction6", f44, 0., 7., NPARAMS);
    Dfunction6 -> SetParameters(par);
    SetUpFunc(Dfunction6, color);
    Dfunction6 -> Draw("same");
    PutEnergy(4., 1.e-2, 45.);

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
    SetUpDiffXSGraph(Dgr5);
//    Dfunction5 ->SetLineWidth(3);
//    Dfunction5 -> Draw("same");
    PutEnergy(4., 1.e-2, 7000);

    theCanvasTOTEM -> Modified();
    //theCanvasTOTEM -> Print("plots\\separate_fit_each_energy\\7000GeV.eps");

    if (false) {
        const int first_param = 8;
        const int last_param = 17;
        TString strEne("DP");
        TString str_postfix("PP_");
        str_postfix += strEne;
        str_postfix += ".csv";
        TString filename(TString("chi2_") + str_postfix);
        ofstream file(filename.Data());
        file << strEne.Data() << " GeV, " << "$\\chi^2$/NDF," << minChi2 / NDF << std::endl;
        for (int k = first_param; k < last_param; k++) {
            float rel_err = minParErr[k] / minPar[k];
            //int prec = 
            file . setf(std::ios::left);
            file << "$" << min->VariableName(k) << "$" << ",";
            file . unsetf(std::ios::left);
            //file . setf( ios::fixed,ios::floatfield );
            //file . setf( ios::showpos );
            //file << fixed;
            file << std::setw(20);
            file << std::fixed
                    << std::setprecision(abs(Order(minParErr[k]) - Order(minPar[k])) + SigDig(minParErr[k]) - 1);
            file << Result(minPar[k], minParErr[k]) * TMath::Power(10., -Order(minPar[k])) << ",";
            file << std::setw(20);
            file << std::fixed;
            file << std::setprecision(abs(Order(minParErr[k]) - Order(minPar[k])) + SigDig(minParErr[k]) - 1)
                    << AbsErr(minParErr[k])*(TMath::Power(10., Order(minParErr[k]) - Order(minPar[k])));
            file << std::setw(10);
            if (Order(minPar[k]) == 0) file << "," << std::endl;
            else file << ", " << "$\\times 10^{" << Order(minPar[k]) << "}$" << std::endl;
        }
        file.close();

        str_postfix = "PP_";
        str_postfix += strEne;
        str_postfix += ".arr";
        TString file1name(TString() + str_postfix);
        ofstream file1(file1name.Data());
        file1 << "Double_t Dpar[" << NPARAMS << "] = { " << std::endl;
        for (int k = 0; k < NPARAMS - 1; k++) file1 << minPar[k] << ", " << std::endl;
        file1 << minPar[NPARAMS - 1] << "};" << std::endl;
        file1.close();

    }


    timer.Stop();
    printf("Time at the end of job = %f seconds\n", timer.CpuTime());

    return;
}
