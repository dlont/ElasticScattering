#include "TROOT.h"
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
#include "TRandom3.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include <cstdio>

#define NPARAMS 20




#include "FinalPlots_Routines/GRAPHFunctionPPCS_dt.cxx"
#include "FinalPlots_Routines/GRAPHFunctionPPCS_dtNOSCALE.cxx"

#include "FinalPlots_Routines/GRAPHFunctionBarPPCS_dt.cxx"
#include "FinalPlots_Routines/GRAPHFunctionBarPPCS_dtNOSCALE.cxx"

void SetUpPadTot(TCanvas* pad) {
    pad -> SetLogx();
    //pad -> SetGridx();
    //pad -> SetGridy();	

    return;
}

void SetUpPadDif(TCanvas* pad) {
    pad -> SetLogy();
    //pad -> SetGridx();
    //pad -> SetGridy();	

    return;
}

void SetUpTotalXSGraph(TGraph* graph, Double_t scale = 1.) {
    //Scale data points and errors
    Int_t nPoints = graph -> GetN();
    Double_t* y = graph -> GetY();
    Double_t* ye = graph -> GetEY();
    for (Int_t i = 0; i < nPoints; i++) {
        y[i] *= scale;
        ye[i] *= scale;
    }

    graph -> SetMarkerStyle(25);
    graph -> SetMarkerSize(0.5);
    graph -> Draw("samePE");
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

void SetUpDiffXSGraph(TGraph* graph, Double_t scale = 1.) {
    //Scale data points and errors
    Int_t nPoints = graph -> GetN();
    Double_t* y = graph -> GetY();
    Double_t* ye = graph -> GetEY();
    for (Int_t i = 0; i < nPoints; i++) {
        y[i] *= scale;
        ye[i] *= scale;
    }

    graph -> SetMarkerStyle(25);
    graph -> SetMarkerSize(0.5);
    graph -> Draw("samePE");
    graph -> GetXaxis() -> SetTitle("-t   (GeV^{2})");
    graph -> GetXaxis() -> CenterTitle(true);
    graph -> GetXaxis() -> SetTitleOffset(1.15);
    graph -> GetXaxis() -> SetLabelFont(132);
    graph -> GetXaxis() -> SetTitleFont(132);
    graph -> GetYaxis() -> SetTitle("\\frac{d#sigma}{dt}   (mb/GeV^{2})");
    graph -> GetYaxis() -> CenterTitle(true);
    graph -> GetYaxis() -> SetTitleOffset(1.55);
    graph -> GetYaxis() -> SetLabelFont(132);
    graph -> GetYaxis() -> SetTitleFont(132);

    return;
}

void SetUpFunc(TF1* function, Int_t color = kRed, Int_t style = 0) {
    function -> SetTitle();
    function -> SetNpx(1000);
    function -> SetLineColor(color);
    function -> SetLineStyle(style);
    function -> SetLineWidth(3);

    return;
}

void DrawFuncUncertainty(TF1* function, Double_t* minPar, Double_t* minParErr, Int_t color = kRed) {
    Double_t max_cs = 0;
    TRandom3 Randomiser;
    Double_t K_parameterValue = 0.;
    Double_t K_parameterError = -1.;
    function -> SetLineColor(color);
    for (Int_t i = 0; i <= 35; i++) {
        for (Int_t par_num = 0; par_num < 22; par_num++) {
            K_parameterValue = minPar[ par_num ];
            K_parameterError = minParErr[ par_num ];
            if (K_parameterError == 0.) continue;
            function -> SetParameter(par_num, Randomiser.Gaus(K_parameterValue, K_parameterError));
            //if( function(14000.) > max_cs ) max_cs=function(14000.);
            function -> DrawCopy("lsame");
        }
    }
    //cout << max_cs << endl;
}

void PutLabelsPP() {
    TLatex * tex = new TLatex(9.433166, 1.988447, "PP");
    tex->SetTextFont(132);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.422739, 0.00121476, "23.5 GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.224874, 4.780999e-006, "30.7 GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.125942, 1.072656e-09, "52.8 GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.048995, 1.26821e-011, "62.0 GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.048995, 1.26821e-07, "44.6 GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.248995, 1.26821e-15, "7.0 TeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.1313, 3.05887e-006, "(x 10)");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.596796, 1.237876e-015, "(x 10^{-7})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(8.30269, 1.48504e-014, "(x 10^{-5})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.06552, 2.60928e-009, "(x 10^{-1})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(7.46601, 7.99234e-012, "(x 10^{-3})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.62601, 9.99234e-017, "(x 10^{-10})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
}

void PutLabelsPPbar() {
    TLatex *tex = new TLatex(3.458166, 1.988447, "P\\bar{P}");
    tex->SetTextFont(132);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.922739, 1.762246e-002, "31. GeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.524874, 1.780999e-006, "53. GeV ( x 10^{-1} )");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.975942, 0.572656e-06, "62 GeV  ( x 10^{-4} )");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(1.548995, 1.26821e-9, "546. GeV  ( x 10^{-6} )");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.048995, 3.26821e-12, "630. GeV  ( x 10^{-8} )");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(0.7548995, 3.96821e-013, "1800. GeV  ( x 10^{-10} )");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.596796, 2.137876e-014, "(x 10^{-6})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(9.39711, 4.2682e-012, "(x 10^{-4})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.06552, 2.60928e-009, "(x 10^{-2})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(6.06552, 2.60928e-009, "(x 10^{-2})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
}

void PutLabelsLHC() {
    TLatex * tex = new TLatex(5.98166, 48.158447, "PP");
    tex->SetTextFont(132);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.422739, 0.000421476, "7 TeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.224874, 6.780999e-006, "10 TeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.125942, 1.072656e-07, "14 TeV");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.62312, 1.95394e-006, "(x10^{-2})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.42211, 3.51443e-008, "(x10^{-4})");
    tex->SetTextFont(132);
    tex->SetTextSize(0.02496503);
    tex->SetLineWidth(2);
    tex->Draw();
}

#include "PPbar_DL.arr"

Double_t par[23];

//	Path input file with hadrons CSs
//	Total cross sections
const char *Tfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\total\\pp_total_root_plot.txt";
const char *Tfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\total\\pbarp_total_root_plot.txt";

//	Differential cross sections
const char *Dfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\PP_ds_dt23_5.txt";
const char *Dfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\PP_ds_dt30_7.txt";
const char *Dfile_name3 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\PP_ds_dt53_0.txt";
const char *Dfile_name4 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\PP_ds_dt62_5.txt";
const char *Dfile_name6 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\PP_ds_dt44_699.txt";
const char *Dfile_name7 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\DATA_TOTEM\\pp_totem_data_err0_35_7TeV.txt";
const char *_Dfile_name1 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt31.txt";
const char *_Dfile_name2 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt53.txt";
const char *_Dfile_name3 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt62.txt";
const char *_Dfile_name4 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt546.txt";
const char *_Dfile_name5 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt630.txt";
const char *_Dfile_name6 = "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\ds_dt_NEW\\barPP_ds_dt1800.txt";

Bool_t doPrint = kFALSE;
TString format(".eps");
TString name_tot("total");
TString name_difPP("difPP");
TString name_difBarPP("difBarPP");
TString name_LHC("LHC");
TString name_ReIm("ReImContrib");

void Fit() {
    ////	Total cross sections graphs
    //TGraphErrors* Tgr1;
    //TGraphErrors* Tgr2;

    //	Differential cross sections graphs for PP
    TGraphErrors* Dgr1;
    TGraphErrors* Dgr2;
    TGraphErrors* Dgr3;
    TGraphErrors* Dgr4;
    TGraphErrors* Dgr6;
    TGraphErrors* Dgr7;

    //	Differential cross sections graphs for \bar PP
    TGraphErrors* _Dgr1;
    TGraphErrors* _Dgr2;
    TGraphErrors* _Dgr3;
    TGraphErrors* _Dgr4;
    TGraphErrors* _Dgr5;
    TGraphErrors* _Dgr6;

    ////////////////////////////////////////////TOTAL//////////////////////////////////////////////
    //TCanvas* theCanvas = new TCanvas( "Canvas", "PPbar, PP total cross sections", 30, 30, 800, 800);
    //theCanvas -> SetGrayscale();
    //SetUpPadTot( theCanvas );
    //Tgr1 = new TGraphErrors( Tfile_name1, "%lg %lg %lg");
    //Tgr1 -> Draw("AP");
    //Tgr1 -> GetXaxis() -> SetLimits(1.001,5.e4);
    //Tgr1 -> GetXaxis() -> SetRangeUser(1.001,5.e4);
    //SetUpTotalXSGraph( Tgr1 );
    //Tgr1 -> SetMarkerStyle(21);

    //Tgr2 = new TGraphErrors( Tfile_name2, "%lg %lg %lg");
    //SetUpTotalXSGraph( Tgr2 );
    //Tgr2 -> SetMarkerStyle(25);

    //TLegend* leg = new TLegend(0.2,0.7,0.3,0.8);
    //leg -> SetLineColor(0);
    //leg -> SetFillColor(0);
    //leg -> SetShadowColor(0);
    //leg -> AddEntry(Tgr1,"PP","p");
    //leg -> AddEntry(Tgr2,"P\\barP","p");
    //leg -> Draw();

    //TLatex *   tex = new TLatex(2022.724,87.57547,"TEVATRON");
    //tex->SetTextSize(0.02832861);
    //tex->SetTextAngle(90);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(1053.435,44.5566,"UA5");
    //tex->SetTextSize(0.02832861);
    //tex->SetTextAngle(90);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(622.832,44.2736,"UA4");
    //tex->SetTextSize(0.02832861);
    //tex->SetTextAngle(90);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(21333.81,64.08491,"{");
    //tex->SetTextFont(42);
    //tex->SetTextSize(0.1388102);
    //tex->SetTextAngle(90);
    //tex->Draw();
    //tex = new TLatex(5005.517,54.46226,"Cosmic ray");
    //tex->SetTextSize(0.02832861);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(8874.6,49.46226,"data");
    //tex->SetTextSize(0.02832861);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(40.3612,49.6509,"ISR");
    //tex->SetTextSize(0.02832861);
    //tex->SetTextAngle(90);
    //tex->SetLineWidth(2);
    //tex->Draw();

    //tex = new TLatex(7403.66,157.1981,"LHC");
    //tex->SetTextSize(0.03124646);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(5381.829,152.3868,"7TeV");
    //tex->SetTextSize(0.02124646);
    //tex->SetLineWidth(2);
    //tex->Draw();
    //tex = new TLatex(10333.77,152.3868,"14TeV");
    //tex->SetTextSize(0.02124646);
    //tex->SetLineWidth(2);
    //tex->Draw();

    //TArrow *arrow = new TArrow(7000.0,149.462,7000.0,136.8208,0.01,">");
    //arrow->SetFillColor(1);
    //arrow->SetFillStyle(1001);
    //arrow->SetLineWidth(3);
    //arrow->Draw();
    //arrow = new TArrow(14000,149.745,14000.0,137.1038,0.01,">");
    //arrow->SetFillColor(1);
    //arrow->SetFillStyle(1001);
    //arrow->SetLineWidth(3);
    //arrow->Draw();

    //theCanvas -> Modified();
    //theCanvas -> Update();

    ////////////////////////////////////////////DIFFERENTIAL PP////////////////////////////////////
    TCanvas* theCanvasD = new TCanvas("CanvasD", "PP differential cross sections", 130, 30, 800, 800);
    //theCanvasD -> SetGrayscale();
    SetUpPadDif(theCanvasD);
    theCanvasD -> GetPad(0) -> SetLeftMargin(0.2);

    Dgr1 = new TGraphErrors(Dfile_name1, "%lg %lg %lg");
    Dgr1 -> Draw("AP");
    Dgr1 -> GetXaxis() -> SetLimits(-0.1, 11.);
    Dgr1 -> GetYaxis() -> SetRangeUser(1e-18, 100.);
    SetUpDiffXSGraph(Dgr1, 1e1);
    Dgr1 -> SetMarkerStyle(21);

    Dgr2 = new TGraphErrors(Dfile_name2, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr2, 1e-1);
    Dgr2 -> SetMarkerStyle(21);

    Dgr3 = new TGraphErrors(Dfile_name3, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr3, 1e-5);
    Dgr3 -> SetMarkerStyle(21);
    Dgr3 -> RemovePoint(Dgr3 -> GetN() - 1);
    Dgr3 -> RemovePoint(Dgr3 -> GetN() - 1);
    Dgr3 -> RemovePoint(Dgr3 -> GetN() - 1);
    Dgr3 -> RemovePoint(Dgr3 -> GetN() - 1);

    Dgr4 = new TGraphErrors(Dfile_name4, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr4, 1e-7);
    Dgr4 -> SetMarkerStyle(21);

    Dgr6 = new TGraphErrors(Dfile_name6, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr6, 1e-3);
    Dgr6 -> SetMarkerStyle(21);

    Dgr7 = new TGraphErrors(Dfile_name7, "%lg %lg %lg");
    SetUpDiffXSGraph(Dgr7, 1e-11);
    Dgr7 -> SetMarkerStyle(21);

    PutLabelsPP();

    theCanvasD -> Modified();
    theCanvasD -> Update();

    ////////////////////////////////////////////DIFFERENTIAL BAR PP////////////////////////////////////
    TCanvas* theCanvasD_ = new TCanvas("CanvasD_", "PPbar differential cross sections", 230, 30, 800, 800);
    //theCanvasD_ -> SetGrayscale();
    SetUpPadDif(theCanvasD_);
    theCanvasD_ -> GetPad(0) -> SetLeftMargin(0.2);

    theCanvasD_ -> cd(1);
    _Dgr1 = new TGraphErrors(_Dfile_name1, "%lg %lg %lg");
    _Dgr1 -> Draw("AP");
    _Dgr1 -> GetXaxis() -> SetLimits(-0.1, 4.);
    _Dgr1 -> GetYaxis() -> SetRangeUser(1e-15, 100.);
    SetUpDiffXSGraph(_Dgr1);

    _Dgr2 = new TGraphErrors(_Dfile_name2, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr2, 1e-1);

    _Dgr3 = new TGraphErrors(_Dfile_name3, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr3, 1e-4);

    _Dgr4 = new TGraphErrors(_Dfile_name4, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr4, 1e-6);

    _Dgr5 = new TGraphErrors(_Dfile_name5, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr5, 1e-8);

    _Dgr6 = new TGraphErrors(_Dfile_name6, "%lg %lg %lg");
    SetUpDiffXSGraph(_Dgr6, 1e-10);

    PutLabelsPPbar();

    theCanvasD_ -> Modified();
    theCanvasD_ -> Update();

    ////////////////////////////////////////////TOTAL//////////////////////////////////////////////
    par[0] = Dpar[0];
    par[4] = Dpar[4];
    par[1] = Dpar[1];
    par[5] = Dpar[5];
    par[2] = Dpar[2];
    par[6] = Dpar[6];
    par[3] = Dpar[3];
    par[7] = Dpar[7];

    par[8] = Dpar[8];
    par[15] = Dpar[15];
    par[9] = Dpar[9];
    par[16] = Dpar[16];
    par[10] = Dpar[10];
    par[17] = Dpar[17];
    par[11] = Dpar[11];
    par[18] = Dpar[18];
    par[12] = Dpar[12];
    par[19] = Dpar[19];
    par[13] = Dpar[13];
    par[20] = Dpar[20];
    par[14] = Dpar[14];
    Int_t color = kRed;

    //theCanvas -> cd();
    //TF1* function1 = new TF1( "function1", FunctionPPCS, 5., 50000., 23);
    //function1 -> SetParameters( par);
    //SetUpFunc( function1, color );		function1 -> Draw( "same" );
    ////DrawFuncUncertainty( function1, par, parErr, kYellow );
    //SetUpFunc( function1, color );
    //function1 -> DrawCopy( "lsame" );
    //cout << "cs: 7TeV\t" << function1(14000.) << endl;

    //TF1* function2 = new TF1( "function2", FunctionPPbarCS, 5., 1900., 23);
    //function2 -> SetParameters( par);
    //SetUpFunc( function2, color );		function2 -> Draw( "same" );
    ////DrawFuncUncertainty( function2, par, parErr, kYellow );
    //SetUpFunc( function2, color );
    //function2 -> SetLineStyle( 2 );
    //function2 -> DrawCopy( "lsame" );

    //Tgr1 -> Draw("pesame");
    //Tgr2 -> Draw("pesame");

    //////////////////////////////////////////////DIFFERENTIAL PP////////////////////////////////////
    theCanvasD -> cd();
    TF1* Dfunction1 = new TF1("Dfunction1", GRAPHFunctionPPCS_dt, 0., 5.8, 23);
    Dfunction1 -> SetParameters(par);
    Dfunction1 -> SetParameter(NPARAMS + 1, 23.503 * 23.503);
    SetUpFunc(Dfunction1, color);
    Dfunction1 -> Draw("same");
    //cout << "Integral: " << Dfunction1 -> Integral(0.,25.)*1e-1 << endl;
    //cout << "Derivative: " << Dfunction1 -> Derivative(0.1) / Dfunction1(0.1) << endl;
    //	DrawFuncUncertainty( Dfunction1, par, parErr );

    TF1* Dfunction2 = new TF1("Dfunction2", GRAPHFunctionPPCS_dt, 0., 5.9, 23);
    Dfunction2 -> SetParameters(par);
    Dfunction2 -> SetParameter(NPARAMS + 1, 30.7 * 30.7);
    SetUpFunc(Dfunction2, color);
    Dfunction2 -> Draw("same");
    //	DrawFuncUncertainty( Dfunction2, par, parErr );

    TF1* Dfunction3 = new TF1("Dfunction3", GRAPHFunctionPPCS_dt, 0., 8., 23);
    Dfunction3 -> SetParameters(par);
    Dfunction3 -> SetParameter(NPARAMS + 1, 53. * 53.);
    SetUpFunc(Dfunction3, color);
    Dfunction3 -> Draw("same");
    //	DrawFuncUncertainty( NPARAMS+1, par, parErr );

    TF1* Dfunction4 = new TF1("Dfunction4", GRAPHFunctionPPCS_dt, 0., 6.5, 23);
    Dfunction4 -> SetParameters(par);
    Dfunction4 -> SetParameter(NPARAMS + 1, 62.5 * 62.5);
    SetUpFunc(Dfunction4, color);
    Dfunction4 -> Draw("same");
    //	DrawFuncUncertainty( Dfunction4, par, parErr );

    TF1* Dfunction6 = new TF1("Dfunction6", GRAPHFunctionPPCS_dt, 0., 7.5, 23);
    Dfunction6 -> SetParameters(par);
    Dfunction6 -> SetParameter(NPARAMS + 1, 44.699 * 44.699);
    SetUpFunc(Dfunction6, color);
    Dfunction6 -> Draw("same");
    //	DrawFuncUncertainty( Dfunction6, par, parErr );

    TF1* Dfunction7 = new TF1("Dfunction7", GRAPHFunctionPPCS_dt, 0., 2.5, 23);
    Dfunction7 -> SetParameters(par);
    Dfunction7 -> SetParameter(NPARAMS + 1, 7000. * 7000.);
    SetUpFunc(Dfunction7, color);
    Dfunction7 -> Draw("same");
    //	DrawFuncUncertainty( Dfunction6, par, parErr );

    ////////////////////////////////////////////DIFFERENTIAL BAR PP////////////////////////////////////
    theCanvasD_ -> cd();
    TF1* _Dfunction1 = new TF1("_Dfunction1", GRAPHFunctionBarPPCS_dt, 0., 0.9, 23);
    _Dfunction1 -> SetParameters(par);
    _Dfunction1 -> SetParameter(NPARAMS + 1, 31. * 31.);
    SetUpFunc(_Dfunction1, color);
    _Dfunction1 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction1, par, parErr );

    TF1* _Dfunction2 = new TF1("_Dfunction2", GRAPHFunctionBarPPCS_dt, 0., 3.55, 23);
    _Dfunction2 -> SetParameters(par);
    _Dfunction2 -> SetParameter(NPARAMS + 1, 53. * 53.);
    SetUpFunc(_Dfunction2, color);
    _Dfunction2 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction2, par, parErr );

    TF1* _Dfunction3 = new TF1("_Dfunction3", GRAPHFunctionBarPPCS_dt, 0., 0.9, 23);
    _Dfunction3 -> SetParameters(par);
    _Dfunction3 -> SetParameter(NPARAMS + 1, 62. * 62.);
    SetUpFunc(_Dfunction3, color);
    _Dfunction3 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction3, par, parErr );

    TF1* _Dfunction4 = new TF1("_Dfunction4", GRAPHFunctionBarPPCS_dt, 0., 1.6, 23);
    _Dfunction4 -> SetParameters(par);
    _Dfunction4 -> SetParameter(NPARAMS + 1, 546. * 546.);
    SetUpFunc(_Dfunction4, color);
    _Dfunction4 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction4, par, parErr );

    TF1* _Dfunction5 = new TF1("_Dfunction5", GRAPHFunctionBarPPCS_dt, 0.7, 2.2, 23);
    _Dfunction5 -> SetParameters(par);
    _Dfunction5 -> SetParameter(NPARAMS + 1, 630. * 630.);
    SetUpFunc(_Dfunction5, color);
    _Dfunction5 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction5, par, parErr );

    TF1* _Dfunction6 = new TF1("_Dfunction6", GRAPHFunctionBarPPCS_dt, 0., 0.7, 23);
    _Dfunction6 -> SetParameters(par);
    _Dfunction6 -> SetParameter(NPARAMS + 1, 1800. * 1800.);
    SetUpFunc(_Dfunction6, color);
    _Dfunction6 -> Draw("same");
    //	DrawFuncUncertainty( _Dfunction6, par, parErr );

    if (doPrint) {
        //theCanvas	-> Print(name_tot+format);
        theCanvasD -> Print(name_difPP + format);
        theCanvasD_ -> Print(name_difBarPP + format);
    }

    ////RE+IM parts of Pomeron and Odderon
    //TF1* DfunctionLHC1 = new TF1( "DfunctionLHC1", GRAPHFunctionPPCS_dt, 0., 8., 23);
    //DfunctionLHC1 -> SetParameters( par);	DfunctionLHC1 -> SetParameter( NPARAMS, 7000.*7000.);
    //SetUpFunc( DfunctionLHC1, color );

    //cout<<scientific;
    //cout.precision(5);
    //const Int_t Np = 1000;
    //for ( Int_t i = 0; i < Np; i++ ) {
    //DfunctionLHC1(5./Np*i);
    //}

}

void LHC() {
    TCanvas* theCanvasLHC = new TCanvas("CanvasLHC", "PP differential cross sections at LHC", 130, 30, 800, 800);
    theCanvasLHC -> GetPad(0) -> SetLeftMargin(0.2);

    TF1* DfunctionDummy = new TF1("DfunctionDummy", GRAPHFunctionPPCS_dt, 0., 8., 23);
    DfunctionDummy -> SetParameters(par);
    DfunctionDummy -> SetParameters(par);
    DfunctionDummy -> SetParameter(NPARAMS, 7000. * 7000.);
    SetUpFunc(DfunctionDummy, 0);
    DfunctionDummy -> Draw();

    DfunctionDummy -> GetXaxis() -> SetTitle("-t   (GeV^{2})");
    DfunctionDummy -> GetXaxis() -> CenterTitle(true);
    DfunctionDummy -> GetXaxis() -> SetLabelFont(132);
    DfunctionDummy -> GetXaxis() -> SetTitleFont(132);
    DfunctionDummy -> GetYaxis() -> SetTitle("\\frac{d\\sigma}{dt}  (mb/GeV^{2})");
    DfunctionDummy -> GetYaxis() -> SetTitleOffset(1.55);
    DfunctionDummy -> GetYaxis() -> CenterTitle(true);
    DfunctionDummy -> GetYaxis() -> SetLabelFont(132);
    DfunctionDummy -> GetYaxis() -> SetTitleFont(132);
    theCanvasLHC -> SetLogy(kTRUE);

    par[0] = Dpar[0];
    par[4] = Dpar[4];
    par[1] = Dpar[1];
    par[5] = Dpar[5];
    par[2] = Dpar[2];
    par[6] = Dpar[6];
    par[3] = Dpar[3];
    par[7] = Dpar[7];

    par[8] = Dpar[8];
    par[15] = Dpar[15];
    par[9] = Dpar[9];
    par[16] = Dpar[16];
    par[10] = Dpar[10];
    par[17] = Dpar[17];
    par[11] = Dpar[11];
    par[18] = Dpar[18];
    par[12] = Dpar[12];
    par[19] = Dpar[19];
    par[13] = Dpar[13];
    par[20] = Dpar[20];
    par[14] = Dpar[14];
    par[21] = Dpar[21];
    par[22] = 100.;
    Int_t color = kRed;

    TF1* DfunctionLHC1 = new TF1("DfunctionLHC1", GRAPHFunctionPPCS_dt, 0., 8., 23);
    DfunctionLHC1 -> SetParameters(par);
    DfunctionLHC1 -> SetParameter(NPARAMS, 7000. * 7000.);
    SetUpFunc(DfunctionLHC1, color);
    DfunctionLHC1 -> Draw("same");
    //DrawFuncUncertainty( DfunctionLHC1, par, parErr, kYellow );
    DfunctionLHC1 -> SetParameters(par);
    DfunctionLHC1 -> SetParameter(NPARAMS, 7000. * 7000.);
    SetUpFunc(DfunctionLHC1, color);
    DfunctionLHC1 -> DrawCopy("lsame");

    //const Int_t Np = 10;
    //for ( Int_t i = 0; i < Np; i++ ) {
    //cout.precision(1);
    //cout << scientific << 5./Np*i;
    //cout.precision(5);
    //cout << "\t" << DfunctionLHC1(10./Np*i) << endl;
    //}

    TF1* DfunctionLHC2 = new TF1("DfunctionLHC2", GRAPHFunctionPPCS_dt, 0., 8., 23);
    DfunctionLHC2 -> SetParameters(par);
    DfunctionLHC2 -> SetParameter(NPARAMS, 10000. * 10000.);
    SetUpFunc(DfunctionLHC2, color);
    DfunctionLHC2 -> Draw("same");
    //DrawFuncUncertainty( DfunctionLHC2, par, parErr, kYellow );
    DfunctionLHC2 -> SetParameters(par);
    DfunctionLHC2 -> SetParameter(NPARAMS, 10000. * 10000.);
    SetUpFunc(DfunctionLHC2, color);
    DfunctionLHC2 -> DrawCopy("lsame");

    TF1* DfunctionLHC3 = new TF1("DfunctionLHC3", GRAPHFunctionPPCS_dt, 0., 8., 23);
    DfunctionLHC3 -> SetParameters(par);
    DfunctionLHC3 -> SetParameter(NPARAMS, 14000. * 14000.);
    SetUpFunc(DfunctionLHC3, color);
    DfunctionLHC3 -> Draw("same");
    //DrawFuncUncertainty( DfunctionLHC3, par, parErr, kYellow );
    DfunctionLHC3 -> SetParameters(par);
    DfunctionLHC3 -> SetParameter(NPARAMS, 14000. * 14000.);
    SetUpFunc(DfunctionLHC3, color);
    DfunctionLHC3 -> DrawCopy("lsame");

    //TLegend* leg = new TLegend(0.7,0.7,0.89,0.9);
    ////leg->SetHeader("The Legend Title");
    //leg->AddEntry(DfunctionLHC1,"#sqrt{s} = 7. TeV","l");
    //leg->AddEntry(DfunctionLHC2,"#sqrt{s} = 10. TeV","l");
    //leg->AddEntry(DfunctionLHC3,"#sqrt{s} = 14. TeV","l");
    //leg->Draw();

    PutLabelsLHC();

    if (doPrint) {
        theCanvasLHC -> Print(name_LHC + format);
    }
}

void OdderonPomeron() {
}

//class  MyFunctionObjectEl {
//public:
//// use constructor to customize your function object
//double operator() (double *x, double *p) {
//func_dt -> SetParameter( 22, x[0]*x[0]);
//return ( func_dt -> Integral(0.,15.)/func_tot(x[0]) );
//}
//SetFunction_dt( TF1* f ) {
//func_dt = f;
//}
//SetFunction_tot( TF1* f ) {
//func_tot = f;
//}
//private:
//TF1* func_dt;
//TF1* func_tot;
//};

//class  MyFunctionObjectEl1 {
//public:
//// use constructor to customize your function object
//double operator() (double *x, double *p) {
//func_dt -> SetParameter( 22, x[0]*x[0]);
//return 1.-( func_dt -> Integral(0.,15.)/func_tot(x[0]) );
//}
//SetFunction_dt( TF1* f ) {
//func_dt = f;
//}
//SetFunction_tot( TF1* f ) {
//func_tot = f;
//}
//private:
//TF1* func_dt;
//TF1* func_tot;
//};


//void Elastic()
//{
//TCanvas* theCanvasElastic = new TCanvas( "CanvasElastic", "PP elastic cross sections", 130, 30, 800, 800);
//theCanvasElastic -> SetGrayscale();
//theCanvasElastic -> GetPad(0) -> SetLogx(kTRUE);

//TGraph* Inelgr1 = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\elastic\\ppbar_elastic_tot.txt", "%lg %lg");
//Inelgr1 -> Draw("APE");
//Inelgr1 -> SetMarkerStyle(21);
//Inelgr1 -> GetXaxis() -> SetLimits(20.,20000.);
//Inelgr1 -> GetYaxis() -> SetLimits(0.,1.);
//Inelgr1 -> GetYaxis() -> SetRangeUser(0.,1.);
//Inelgr1 -> GetXaxis() -> SetTitle("\\sqrt{s}   (GeV)");
//Inelgr1 -> GetXaxis() -> CenterTitle( true);
//Inelgr1 -> GetXaxis() -> SetTitleOffset( 1.15);
//Inelgr1 -> GetXaxis() -> SetLabelFont(132);
//Inelgr1 -> GetXaxis() -> SetTitleFont(132);
//Inelgr1 -> GetYaxis() -> SetTitle("\\sigma_{(in)el}/\\sigma_{tot}");
//Inelgr1 -> GetYaxis() -> CenterTitle( true);
//Inelgr1 -> GetYaxis() -> SetLabelFont(132);
//Inelgr1 -> GetYaxis() -> SetTitleFont(132);

//TF1* function_tot = new TF1( "function_tot", FunctionPPbarCS, 5., 50000., 23);
//function_tot -> SetParameters( par);

//TF1* Dfunction = new TF1( "Dfunction", GRAPHFunctionBarPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction -> SetParameters( par);
//Dfunction -> SetParameter( 22, 20.*20.);

//MyFunctionObjectEl * fobj = new MyFunctionObjectEl;
//fobj->SetFunction_dt(Dfunction);
//fobj->SetFunction_tot(function_tot);
//TF1* DfunctionEl = new TF1( "DfunctionEl",fobj,20.,18000.,0,"MyFunctionObjectEl" );

//DfunctionEl -> SetLineColor(kRed);
//DfunctionEl -> SetNpx(100);
//DfunctionEl -> Draw("lsame"); 

//MyFunctionObjectEl1 * fobj1 = new MyFunctionObjectEl1;
//fobj1->SetFunction_dt(Dfunction);
//fobj1->SetFunction_tot(function_tot);
//TF1* DfunctionEl1 = new TF1( "DfunctionEl1",fobj1,20.,18000.,0,"MyFunctionObjectEl1" );

//DfunctionEl1 -> SetLineColor(kRed);
//DfunctionEl1 -> SetLineStyle(5);
//DfunctionEl1 -> SetNpx(100);
//DfunctionEl1 -> Draw("lsame"); 

//TLegend* leg = new TLegend(0.65,0.75,0.85,0.85);
//leg -> SetLineColor(0);
//leg -> SetFillColor(0);
//leg -> SetShadowColor(0);
//leg -> AddEntry(Inelgr1,"P\\bar{P}", "P");
//leg -> AddEntry(DfunctionEl,"\\sigma_{el}/\\sigma_{tot} fit", "L");
//leg -> AddEntry(DfunctionEl1,"\\sigma_{inel}/\\sigma_{tot} fit", "L");
//leg -> Draw();
//}

//class  MyFunctionObject {
//public:
//// use constructor to customize your function object
//double operator() (double *x, double *p) {
//func_dt -> SetParameter( 22, x[0]*x[0]);
//return ( func_tot(x[0]) - func_dt -> Integral(0.,15.) );
//}
//SetFunction_dt( TF1* f ) {
//func_dt = f;
//}
//SetFunction_tot( TF1* f ) {
//func_tot = f;
//}
//private:
//TF1* func_dt;
//TF1* func_tot;
//};

//void Inelastic()
//{
//TCanvas* theCanvasInelastic = new TCanvas( "CanvasInelastic", "PP inelastic cross sections", 130, 30, 800, 800);
//theCanvasInelastic -> SetGrayscale();
//theCanvasInelastic -> GetPad(0) -> SetLogx(kTRUE);

//TGraph* Inelgr1 = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\elastic\\pp_inelastic.txt", "%lg %lg");
//Inelgr1 -> Draw("APE");
//Inelgr1 -> SetMarkerStyle(21);
//Inelgr1 -> GetXaxis() -> SetLimits(20.,18000.);
//Inelgr1 -> GetYaxis() -> SetLimits(0.,100.);
//Inelgr1 -> GetYaxis() -> SetRangeUser(0.,100.);
//Inelgr1 -> GetXaxis() -> SetTitle("\\sqrt{s}   (GeV)");
//Inelgr1 -> GetXaxis() -> CenterTitle( true);
//Inelgr1 -> GetXaxis() -> SetTitleOffset( 1.15);
//Inelgr1 -> GetXaxis() -> SetLabelFont(132);
//Inelgr1 -> GetXaxis() -> SetTitleFont(132);
//Inelgr1 -> GetYaxis() -> SetTitle("\\sigma_{inel}   (mb)");
//Inelgr1 -> GetYaxis() -> CenterTitle( true);
//Inelgr1 -> GetYaxis() -> SetLabelFont(132);
//Inelgr1 -> GetYaxis() -> SetTitleFont(132);

//TGraphErrors* InelgrLHCATLAS = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\elastic\\pp_inelastic_ATLAS.txt", "%lg %lg %lg");
//InelgrLHCATLAS -> SetMarkerStyle(20);
//InelgrLHCATLAS -> SetMarkerColor(kBlack);
//InelgrLHCATLAS -> Draw("PEsame");

//TGraphErrors* InelgrLHCCMS = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\elastic\\pp_inelastic_CMS.txt", "%lg %lg %lg");
//InelgrLHCCMS -> SetMarkerStyle(24);
//InelgrLHCCMS -> SetMarkerColor(kBlack);
//InelgrLHCCMS -> Draw("PEsame");

//TF1* function_tot = new TF1( "function_tot", FunctionPPCS, 5., 50000., 23);
//function_tot -> SetParameters( par);

//TF1* Dfunction = new TF1( "Dfunction", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction -> SetParameters( par);
//Dfunction -> SetParameter( 22, 20.*20.);

//MyFunctionObject * fobj = new MyFunctionObject;
//fobj->SetFunction_dt(Dfunction);
//fobj->SetFunction_tot(function_tot);
//TF1* DfunctionInel = new TF1( "DfunctionInel",fobj,20.,18000.,0,"MyFunctionObject" );

//DfunctionInel -> SetLineColor(kRed);
//DfunctionInel -> SetNpx(100);
//DfunctionInel -> Draw("lsame"); 

//TLegend* leg = new TLegend(0.25,0.65,0.55,0.85);
//leg -> SetLineColor(0);
//leg -> SetFillColor(0);
//leg -> SetShadowColor(0);
//leg -> AddEntry(InelgrLHCATLAS,"PP 7 TeV ATLAS", "P");
//leg -> AddEntry(InelgrLHCCMS,"PP 7 TeV CMS", "P");
//leg -> AddEntry(Inelgr1,"PP 62 GeV ISR", "P");
//leg -> AddEntry(DfunctionInel,"PP 62 GeV fit", "L");
//leg -> Draw();
//}

//class  Slope_tObject {
//public:
//// use constructor to customize your function object
//double operator() (double *x, double *p) {
//return ( -func_dt -> Derivative(x[0])/func_dt(x[0]) );
//}
//SetFunction_dt( TF1* f ) {
//func_dt = f;
//}

//private:
//TF1* func_dt;
//};

//void Slope_t()
//{
//TCanvas* theCanvasSlope_t = new TCanvas( "CanvasSlope_t", "PP elastic cross section slope", 130, 30, 800, 800);
//theCanvasSlope_t -> SetGrayscale();

//TGraphErrors* Inelgr1 = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\slope_1800_GeV_ppbar_maple1_no_last_point.dat", "%lg %lg %lg %lg");
//Inelgr1 -> Draw("APE");
//Inelgr1 -> SetMarkerStyle(25);
//Inelgr1 -> GetXaxis() -> SetLimits(0.,1.0);
//Inelgr1 -> GetYaxis() -> SetLimits(0.,30.);
//Inelgr1 -> GetYaxis() -> SetRangeUser(0.,30.);
//Inelgr1 -> GetXaxis() -> SetTitle("-t   (GeV^{2})");
//Inelgr1 -> GetXaxis() -> CenterTitle( true);
//Inelgr1 -> GetXaxis() -> SetTitleOffset( 1.15);
//Inelgr1 -> GetXaxis() -> SetLabelFont(132);
//Inelgr1 -> GetXaxis() -> SetTitleFont(132);
//Inelgr1 -> GetYaxis() -> SetTitle("B(t)   (GeV^{-2})");
//Inelgr1 -> GetYaxis() -> CenterTitle( true);
//Inelgr1 -> GetYaxis() -> SetLabelFont(132);
//Inelgr1 -> GetYaxis() -> SetTitleFont(132);

//TGraphErrors* Inelgr2 = new TGraphErrors( "D:\\CDF\\Theory_task\\Minisation_pp_CS\\DATA\\LengyelData\\slope_62 GeV pp_maple.dat", "%lg %lg %lg %lg");
//Inelgr2 -> Draw("PEsame");
//Inelgr2 -> SetMarkerStyle(21);

//TF1* _Dfunction = new TF1( "_Dfunction", GRAPHFunctionBarPPCS_dtNOSCALE, 0., 7., 23);
//_Dfunction -> SetParameters( par);
//_Dfunction -> SetParameter( 22, 1800.*1800.);

//Slope_tObject * _fobj = new Slope_tObject;
//_fobj->SetFunction_dt(_Dfunction);
//TF1* functionSlope_t = new TF1( "functionSlope_t",_fobj,0.01,1.0,0,"Slope_tObject" );

//functionSlope_t -> SetLineColor(kRed);
////functionSlope_t -> SetLineStyle(3);
//functionSlope_t -> SetNpx(100);
//functionSlope_t -> Draw("lsame"); 

//TF1* Dfunction1 = new TF1( "Dfunction1", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction1 -> SetParameters( par);
//Dfunction1 -> SetParameter( 22, 7000.*7000.);

//Slope_tObject * fobj1 = new Slope_tObject;
//fobj1->SetFunction_dt(Dfunction1);
//TF1* functionSlope_t1 = new TF1( "functionSlope_t1",fobj1,0.01,1.0,0,"Slope_tObject" );

//functionSlope_t1 -> SetLineColor(kRed);
//functionSlope_t1 -> SetLineStyle(9);
//functionSlope_t1 -> SetNpx(100);
//functionSlope_t1 -> Draw("lsame"); 

//TF1* Dfunction2 = new TF1( "Dfunction2", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction2 -> SetParameters( par);
//Dfunction2 -> SetParameter( 22, 14000.*14000.);

//Slope_tObject * fobj2 = new Slope_tObject;
//fobj2->SetFunction_dt(Dfunction2);
//TF1* functionSlope_t2 = new TF1( "functionSlope_t2",fobj2,0.01,1.0,0,"Slope_tObject" );

//functionSlope_t2 -> SetLineColor(kRed);
//functionSlope_t2 -> SetLineStyle(5);
//functionSlope_t2 -> SetNpx(100);
//functionSlope_t2 -> Draw("lsame"); 

//TF1* Dfunction3 = new TF1( "Dfunction3", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction3 -> SetParameters( par);
//Dfunction3 -> SetParameter( 22, 62.*62.);

//Slope_tObject * fobj3 = new Slope_tObject;
//fobj3->SetFunction_dt(Dfunction3);
//TF1* functionSlope_t3 = new TF1( "functionSlope_t3",fobj3,0.01,1.0,0,"Slope_tObject" );

//functionSlope_t3 -> SetLineColor(kRed);
//functionSlope_t3 -> SetLineStyle(2);
//functionSlope_t3 -> SetNpx(100);
//functionSlope_t3 -> Draw("lsame"); 

//TLegend* leg = new TLegend(0.55,0.65,0.85,0.85);
//leg -> SetLineColor(0);
//leg -> SetFillColor(0);
//leg -> SetShadowColor(0);
//leg -> AddEntry(Inelgr1,"P\\bar{P} 1800 GeV TEVATRON", "P");
//leg -> AddEntry(Inelgr2,"PP 62 GeV ISR", "P");
//leg -> AddEntry(functionSlope_t,"P\\bar{P} 1800 GeV fit","l");
//leg -> AddEntry(functionSlope_t1,"PP 7 TeV fit","l");
//leg -> AddEntry(functionSlope_t2,"PP 14 TeV fit","l");
//leg -> AddEntry(functionSlope_t3,"PP 62 GeV fit","l");
//leg -> Draw();
//}

//class  Slope_sObject {
//public:
//// use constructor to customize your function object
//double operator() (double *x, double *p) {
//func_dt -> SetParameter(22,x[0]);
//return ( -func_dt -> Derivative(t)/func_dt(t) );
//}
//SetFunction_dt( TF1* f ) {
//func_dt = f;
//}

//Set_t( Double_t x ) {
//t = x;
//}

//private:
//TF1* func_dt;
//Double_t t;
//};


//void Slope_s()
//{
//TCanvas* theCanvasSlope_s = new TCanvas( "CanvasSlope_s", "PP elastic cross section slope", 130, 30, 800, 800);
//theCanvasSlope_s -> SetGrayscale();
//theCanvasSlope_s -> GetPad(0) -> SetLogx(kTRUE);

//Double_t x[3] = {62.,62.,62.};
//Double_t y[3] = {.1149E+02,.1114E+02,.1111E+02};
//Double_t ey[3] = {.6702E+00,.5078E+00,.7205E+00};
//TGraphErrors* Inelgr1 = new TGraphErrors(3,x,y,0,ey);
//Inelgr1 -> Draw("APE");
//Inelgr1 -> SetMarkerStyle(25);
//Inelgr1 -> GetXaxis() -> SetLimits(20.,18000.0);
//Inelgr1 -> GetYaxis() -> SetLimits(5.,15.);
//Inelgr1 -> GetYaxis() -> SetRangeUser(5.,15.);
//Inelgr1 -> GetXaxis() -> SetTitle("\\sqrt{s}   (GeV)");
//Inelgr1 -> GetXaxis() -> CenterTitle( true);
//Inelgr1 -> GetXaxis() -> SetTitleOffset( 1.15);
//Inelgr1 -> GetXaxis() -> SetLabelFont(132);
//Inelgr1 -> GetXaxis() -> SetTitleFont(132);
//Inelgr1 -> GetYaxis() -> SetTitle("B(s)   (GeV^{-2})");
//Inelgr1 -> GetYaxis() -> CenterTitle( true);
//Inelgr1 -> GetYaxis() -> SetLabelFont(132);
//Inelgr1 -> GetYaxis() -> SetTitleFont(132);

//TF1* Dfunction1 = new TF1( "Dfunction1", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction1 -> SetParameters( par);

//Slope_sObject * fobj1 = new Slope_sObject;
//fobj1->SetFunction_dt(Dfunction1);
//fobj1->Set_t(0.089);
//TF1* functionSlope_s1 = new TF1( "functionSlope_s1",fobj1,20.,18000.0,0,"Slope_sObject" );

//functionSlope_s1 -> SetLineColor(kRed);
//functionSlope_s1 -> SetLineStyle(9);
//functionSlope_s1 -> SetNpx(100);
//functionSlope_s1 -> Draw("lsame"); 

//TF1* Dfunction2 = new TF1( "Dfunction2", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction2 -> SetParameters( par);

//Slope_sObject * fobj2 = new Slope_sObject;
//fobj2->SetFunction_dt(Dfunction2);
//fobj2->Set_t(0.17);
//TF1* functionSlope_s2 = new TF1( "functionSlope_s2",fobj2,20.,18000.0,0,"Slope_sObject" );

//functionSlope_s2 -> SetLineColor(kRed);
//functionSlope_s2 -> SetLineStyle(5);
//functionSlope_s2 -> SetNpx(100);
//functionSlope_s2 -> Draw("lsame"); 

//TF1* Dfunction3 = new TF1( "Dfunction3", GRAPHFunctionPPCS_dtNOSCALE, 0., 7., 23);
//Dfunction3 -> SetParameters( par);

//Slope_sObject * fobj3 = new Slope_sObject;
//fobj3->Set_t(0.37);
//fobj3->SetFunction_dt(Dfunction3);
//TF1* functionSlope_s3 = new TF1( "functionSlope_s3",fobj3,20.,18000.0,0,"Slope_sObject" );

//functionSlope_s3 -> SetLineColor(kRed);
//functionSlope_s3 -> SetLineStyle(2);
//functionSlope_s3 -> SetNpx(100);
//functionSlope_s3 -> Draw("lsame"); 

//TLegend* leg = new TLegend(0.2,0.7,0.4,0.85);
//leg -> SetLineColor(0);
//leg -> SetFillColor(0);
//leg -> SetShadowColor(0);
//leg -> AddEntry(Inelgr1,"PP 62 GeV ISR", "P");
//leg -> AddEntry(functionSlope_s1,"PP -t=0.089 fit","l");
//leg -> AddEntry(functionSlope_s2,"PP -t=0.17 fit","l");
//leg -> AddEntry(functionSlope_s3,"PP -t=0.37 fit","l");
//leg -> Draw();
//}

void FinalPlots() {
    gROOT->SetStyle("Pub");
    gStyle->SetOptTitle(kFALSE);

    //gROOT->ProcessLine(".L FunctionPPCS.cxx");
    //gROOT->ProcessLine(".L FunctionPPbarCS.cxx");

    Fit();
    //LHC();
    //Elastic();
    //Inelastic();
    //Slope_t();
    //Slope_s();
}
