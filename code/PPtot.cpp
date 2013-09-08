/* 
 * File:   PPtot.cpp
 * Author: Інна_Денис
 * 
 * Created on 30 Август 2013 г., 11:23
 */

#include "PPtot.h"

#include "Utility.h"

#include "TMath.h"
#include "TComplex.h"

#include <iostream>

PPtot::PPtot() : 
Functor(),
_scale(1.)
{
}

PPtot::~PPtot()
{

}

double PPtot::operator() ( double* x, const double *par )
{    
    Double_t s = x[ 0 ] * x[ 0 ];
//    cout << x[0] << endl;
    //
    const Double_t t = 0.;
    const Double_t s_r0 = par[ 16 ];
    const Double_t L = TMath::Log(s / s_r0 );
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
    
    // Energy slope 
    Double_t k_h = par[ 17];
    Double_t p_h = par[ 18];
    Double_t k_s = par[ 19];
    Double_t p_s = par[ 20];

    // Calculating amplitudes
    Double_t w_traj = alpha_w0 + alpha_w*t;
    TComplex Aw = TComplex(0.,1.)*TComplex::Exp( TComplex( 0., -Pi*(w_traj)/2. ) ) * a_w * TMath::Exp( b_w*t ) * TMath::Power( s/s_r0, w_traj );

    Double_t f_traj = alpha_f0 + alpha_f*t;
    TComplex Af = TComplex::Exp( TComplex( 0., -Pi*(f_traj)/2. ) ) * a_f * TMath::Exp( b_f*t ) * TMath::Power( s/s_r0, f_traj );

    
    TComplex A;
    TComplex exp_term_h(b_h + k_h*TMath::Power(L,p_h), 0.);
    TComplex exp_term_s(b_s + k_s*TMath::Power(L,p_s), -Pi/2.);
    
    TComplex alpha_h(alpha_h0 + alpha_h1*t, 0.);
    TComplex alpha_s(alpha_s0 + alpha_s1*t, 0.);

    A = a_h * TComplex::Exp(exp_term_h * alpha_h) + a_s * TComplex::Exp(exp_term_s * alpha_s);
    A += Aw;
    A += Af;
    
    Double_t Im = A.Im();

    return _scale * ( 4 * Pi / s * Im * GEV2MB);

}

void PPtot::setScale(double scale) {
    if ( scale < 0 ) {
        std::cout << "ERROR: Negative energy is not allowed" << std::endl;
        std::cout << "ERROR: Check supplied value: " << scale << std::endl;
        return;
    }
    this->_scale = scale;
}

double PPtot::getScale() const {
    return _scale;
}

