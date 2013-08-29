/*****************************************************
 * 
 * Collection of routines to present scientyfic results
 * Follow PDG convention (see:http://pdg.lbl.gov/2006/reviews/textrpp.pdf (Sec. 5.3 'Rounding') ) 
 * 
 * Denys Lontkovskyi 12.12.2011
 * 
 ****************************************************/

/// 0.00052349 +/- 0.00000123
/// 5.235 +/- 0.012  10^-4

#ifndef SIGDIG_H
#define SIGDIG_H

#include <iostream>
#include "TMath.h"

Int_t SigDig(Double_t err) {
    Int_t nSigDig = 1;

    if (err > 0) {
        Double_t order = floor(TMath::Log10(err));
        Double_t Sign = (order > 0) ? 1 : ((order < 0) ? -1 : 0);
        Int_t abs_err_4dig = err * TMath::Power(10., -order) * 1000;
        Int_t abs_err_3dig = err * TMath::Power(10., -order) * 100;
        Int_t abs_err_2dig = err * TMath::Power(10., -order) * 10;
        Int_t abs_err_1dig = err * TMath::Power(10., -order) * 1;
        if (abs_err_2dig - 10 * abs_err_1dig >= 5) abs_err_1dig++;
        if (abs_err_3dig - 10 * abs_err_2dig >= 5) abs_err_2dig++;
        if (abs_err_4dig - 10 * abs_err_3dig >= 5) abs_err_3dig++;

        if (abs_err_3dig >= 100 && abs_err_3dig <= 354) {
            nSigDig = 2;
        } else if (abs_err_3dig >= 355 && abs_err_3dig <= 949) {
            nSigDig = 1;
        } else {
            nSigDig = 2;
        }
    } else {
//        std::cout << "ERROR: SigDig() " << std::endl;
//        std::cout << "Uncertainty is wrong: " << err << std::endl;
    }

    return nSigDig;
}

Double_t Result(Double_t res, Double_t err) {
    Double_t Result = 0.;

    Int_t nSigDig = SigDig(err);
    
    Int_t ErrOrder = 1.;
    if ( err > 0 ) ErrOrder = floor(TMath::Log10(err));

    ///0.00052349 +/- 0.00000123	--->
    Double_t order = floor(TMath::Log10(res));
    ///52349 +/- 123
    Int_t abs_res_3dig = res * TMath::Power(10., (-ErrOrder + 2)) * 1;
    ///5234 +/- 12
    Int_t abs_res_2dig = res * TMath::Power(10., (-ErrOrder + 2)) * 0.1;
    ///523 +/- 1
    Int_t abs_res_1dig = res * TMath::Power(10., (-ErrOrder + 2)) * 0.01;

    ///5234 --->  5230
    if (abs_res_2dig - 10 * abs_res_1dig >= 5) abs_res_1dig++;
    ///52349 --->  52350
    if (abs_res_3dig - 10 * abs_res_2dig >= 5) abs_res_2dig++;

    if (nSigDig == 2) {
        Result = (Double_t) abs_res_2dig * TMath::Power(10., -(-ErrOrder + 2)) * 10;
    } else if (nSigDig == 1) {
        Result = (Double_t) abs_res_1dig * TMath::Power(10., -(-ErrOrder + 2)) * 100;
    }

    return Result;

}

Int_t Order(Double_t val) {
    Int_t order = 0;
    if (val > 0) {
        order = floor(TMath::Log10(val));
    } else {
//        std::cout << "ERROR: Order()" << std::endl;
//        std::cout << "Negative value of argument: " << val << std::endl;
    }
    return order;
}

///Reduces order if belongs to range 950 999

Int_t ErrOrder(Double_t err) {
    Double_t order = 0;
    if (err > 0) {
        order = floor(TMath::Log10(err));
        Double_t Sign = (order > 0) ? 1 : ((order < 0) ? -1 : 0);
        Int_t abs_err_4dig = err * TMath::Power(10., -order) * 1000;
        Int_t abs_err_3dig = err * TMath::Power(10., -order) * 100;
        Int_t abs_err_2dig = err * TMath::Power(10., -order) * 10;
        Int_t abs_err_1dig = err * TMath::Power(10., -order) * 1;
        if (abs_err_2dig - 10 * abs_err_1dig >= 5) abs_err_1dig++;
        if (abs_err_3dig - 10 * abs_err_2dig >= 5) abs_err_2dig++;
        if (abs_err_4dig - 10 * abs_err_3dig >= 5) abs_err_3dig++;

        if (abs_err_3dig >= 100 && abs_err_3dig <= 354) {
            ;
        } else if (abs_err_3dig >= 355 && abs_err_3dig <= 949) {
            ;
        } else {
            order++;
        }
    } else {
//        std::cout << "ERROR: ErrOrder()" << std::endl;
//        std::cout << "Negative value of argument: " << err << std::endl;
    }

    return order;
}

Int_t Precision(Double_t val) {
    return val - 1;
}

Double_t AbsErr(Double_t err) {
    Double_t AbsErr = 0.;

    if (err > 0) {
        Double_t order = floor(TMath::Log10(err));
        Double_t Sign = (order > 0) ? 1 : ((order < 0) ? -1 : 0);
        Int_t abs_err_4dig = err * TMath::Power(10., -order) * 1000;
        Int_t abs_err_3dig = err * TMath::Power(10., -order) * 100;
        Int_t abs_err_2dig = err * TMath::Power(10., -order) * 10;
        Int_t abs_err_1dig = err * TMath::Power(10., -order) * 1;
        if (abs_err_2dig - 10 * abs_err_1dig >= 5) abs_err_1dig++;
        if (abs_err_3dig - 10 * abs_err_2dig >= 5) abs_err_2dig++;
        if (abs_err_4dig - 10 * abs_err_3dig >= 5) abs_err_3dig++;

        if (abs_err_3dig >= 100 && abs_err_3dig <= 354) {
            AbsErr = (Double_t) abs_err_2dig * 0.1;
        } else if (abs_err_3dig >= 355 && abs_err_3dig <= 949) {
            AbsErr = (Double_t) abs_err_1dig * 1.;
        } else {
            AbsErr = 1.;
        }
    } else {
//        std::cout << "ERROR: AbsErr()" << std::endl;
//        std::cout << "Negative value of argument: " << err << std::endl;
    }
    return AbsErr;
}

#endif /* SIGDIG_H */