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

#define NPARAMS 21

#include "code/Functor.h"
#include "code/PPdsdtTdependentPhase.h"

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
const char *Dfile_name7 = "D:\\CDF\\Theory_task\\Minisation_pp_CS_BARGER_PHILLIPS\\FIT\\DATA_TOTEM\\pp_official_totem_data_7TeV.txt";
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

    Int_t color = kRed;

    //////////////////////////////////////////////DIFFERENTIAL PP////////////////////////////////////
    theCanvasD -> cd();
 
    #include "parameters/best_f_soft_hard.inc"
    Double_t par[NPARAMS];
    for ( int ipar = 0; ipar < NPARAMS; ++ipar ) {
        par[ ipar ] = ipar[ ipar ].second;
    }
    
    double s = 23.503*23.503;
    Functor* f23 = new PPdsdtTdependentPhase( s );
    f23->setScale(1.);
    TF1* Dfunction1 = new TF1("Dfunction1", f23, 0., 5.8, 23);
    Dfunction1 -> SetParameters(par);
    SetUpFunc(Dfunction1, color);
    Dfunction1 -> Draw("same");
    //cout << "Integral: " << Dfunction1 -> Integral(0.,25.)*1e-1 << endl;
    //cout << "Derivative: " << Dfunction1 -> Derivative(0.1) / Dfunction1(0.1) << endl;
    //	DrawFuncUncertainty( Dfunction1, par, parErr );

    s = 30.7*30.7;
    Functor* f31 = new PPdsdtTdependentPhase( s );
    f31->setScale(1.);
    TF1* Dfunction2 = new TF1("Dfunction2", f31, 0., 5.9, 23);
    Dfunction2 -> SetParameters(par);
    SetUpFunc(Dfunction2, color);
    Dfunction2 -> Draw("same");

    s = 53.0*53.0;
    Functor* f53 = new PPdsdtTdependentPhase( s );
    f53->setScale(1.);
    TF1* Dfunction3 = new TF1("Dfunction3", f53, 0., 8., 23);
    Dfunction3 -> SetParameters(par);
    SetUpFunc(Dfunction3, color);
    Dfunction3 -> Draw("same");
    
    s = 62.5*62.5;
    Functor* f63 = new PPdsdtTdependentPhase( s );
    f63->setScale(1.);
    TF1* Dfunction4 = new TF1("Dfunction4", f63, 0., 6.5, 23);
    Dfunction4 -> SetParameters(par);
    SetUpFunc(Dfunction4, color);
    Dfunction4 -> Draw("same");

    s = 44.699*44.699;
    Functor* f44 = new PPdsdtTdependentPhase( s );
    f44->setScale(1.);
    TF1* Dfunction6 = new TF1("Dfunction6", f44, 0., 7.5, 23);
    Dfunction6 -> SetParameters(par);
    SetUpFunc(Dfunction6, color);
    Dfunction6 -> Draw("same");

    s = 7000.*7000.;
    Functor* f7000 = new PPdsdtTdependentPhase( s );
    f7000->setScale(1.);
    TF1* Dfunction7 = new TF1("Dfunction7", f7000, 0., 2.5, 23);
    Dfunction7 -> SetParameters(par);
    SetUpFunc(Dfunction7, color);
    Dfunction7 -> Draw("same");

    if (doPrint) {
        theCanvasD -> Print(name_difPP + format);
    }
}

void Plot() {
    gROOT->SetStyle("Pub");
    gStyle->SetOptTitle(kFALSE);

    Fit();
}
