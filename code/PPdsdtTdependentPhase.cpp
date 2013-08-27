/* 
 * File:   PPdsdtTdependentPhase.cpp
 * Author: dlont@gmail.com
 * 
 * Created on 27 Август 2013 г., 23:00
 */

#include "PPdsdtTdependentPhase.h"
#include "Utility.h"

#include "TMath.h"
#include "TComplex.h"

#include <iostream>

PPdsdtTdependentPhase::PPdsdtTdependentPhase() : 
Functor(),
_s(-1.)
{
}

PPdsdtTdependentPhase::PPdsdtTdependentPhase( double s ) :
Functor(),
_s(s)
{
}

PPdsdtTdependentPhase::~PPdsdtTdependentPhase()
{

}

double PPdsdtTdependentPhase::operator() ( double* x, const double *par )
{
    if ( _s < 0. ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Center of mass energy is unphysical: " << _s << std::endl;
    }
    
    Double_t s = _s;
    //
    const Double_t t = -x[ 0];
    const Double_t s_r0 = par[ 16 ];
    const Double_t L = TMath::Log(s / s_r0);
    //
    Double_t termA_w = 0.;
    Double_t termA_f = 0.;
    Double_t termA_P = 0.;
    Double_t termA_O = 0.;
    //
    const Double_t Pi = TMath::Pi();
    //w-Reggeon parameeters
    Double_t a_w = par[ 0 ];
    Double_t b_w = par[ 3 ];
    Double_t alpha_w0 = par[ 1 ]; //w Regge tr. intercept
    Double_t alpha_w = par[ 2 ]; //w Regge tr. slope
    //f-Reggeon parameters
    Double_t a_f = par[ 4 ];
    Double_t b_f = par[ 7 ];
    Double_t alpha_f0 = par[ 5 ]; //f Regge tr. intercept
    Double_t alpha_f = par[ 6 ]; //f Regge tr. slope
    /*------------------------------- Pomeron parameters ---------------------*/
    // Hard pomeron parametes
    Double_t a_h = par[ 8 ];
    Double_t b_h = par[ 9 ];
    Double_t alpha_h0 = par[ 10];
    Double_t alpha_h1 = par[ 11];
    
    // Soft pomeron parametes
    Double_t a_s = par[ 12 ];
    Double_t b_s = par[ 13 ];
    Double_t alpha_s0 = par[ 14];
    Double_t alpha_s1 = par[ 15];

    // Calculating amplitudes
    TComplex A;

    TComplex exp_term_h(b_h + L, -Pi/2.);
    TComplex exp_term_s(b_s + L, -Pi/2.);
    
    TComplex alpha_h(alpha_h0 + alpha_h1*t, 0.);
    TComplex alpha_s(alpha_s0 + alpha_s1*t, 0.);

    A = a_h * TComplex::Exp(exp_term_h * alpha_h) + a_s * TComplex::Exp(exp_term_s * alpha_s);

    Double_t Im = A.Im();
    Double_t Re = A.Re();

    Double_t Im2 = Im * Im;
    Double_t Re2 = Re * Re;

    return ( (Pi / (s * s)) * (Re2 + Im2) * GEV2MB);

}

/**
 * Set centre of mass energy
 * @param sqrtS centre of mass energy
 */
void PPdsdtTdependentPhase::setSqrtS(double sqrtS) {
    this->_s = sqrtS;
}

/**
 * Get centre of mass energy
 * @return sqrt(s)
 */
double PPdsdtTdependentPhase::getSqrtS() const {
    return _s;
}

