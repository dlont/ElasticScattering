/*

 * ppdsdt.cpp

 *

 */



#include <iostream>

#include "PPdsdt.h"
#include "Utility.h"

#include "TMath.h"
#include "TComplex.h"

PPdsdt::PPdsdt() : 
Functor(),
_s(-1.)
{

}

PPdsdt::PPdsdt( double s ) :
Functor(),
_s(s)
{
}

PPdsdt::~PPdsdt()
{

}

double PPdsdt::operator() ( double* x, const double *par )
{
    if ( _s < 0. ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Center of mass energy is unphysical: " << _s << std::endl;
    }
    
    Double_t s = _s;
    //
    const Double_t t = -x[ 0];
    const Double_t s_0r = par[ 17];
    const Double_t L = TMath::Log(s / s_0r);
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
    //Pomeron parametes
    Double_t a = par[ 8 ];
    Double_t b1 = par[ 9 ];
    Double_t b2 = par[ 10];
    Double_t c = par[ 11];
    Double_t d1 = par[ 12];
    Double_t d2 = par[ 13];
    Double_t eps1 = par[ 14];
    Double_t eps2 = par[ 15];
    Double_t phi = par[ 16];

    Double_t a_o = par[ 17];
    Double_t c_o = par[ 18];
    Double_t phi2_o = par[ 19];

    //Calculating BP pomeron
    TComplex A;
    Double_t A1 = a;
    Double_t C1 = c;
    Double_t b = b1;
    Double_t d = d1;
    //Double_t sqrtbrake = b2 * TMath::Sqrt( 4.* d2 - t );
    //Double_t b = b1+b2*L;
    //Double_t d = d1+d2*L;

    //Double_t A1 = a * TMath::Power(s/s_0r,eps1);
    //Double_t C1 = c * TMath::Power(s/s_0r,eps2);
    //Double_t A1 = a * TMath::Power(s/s_0r,eps1)*L;
    //Double_t C1 = c * TMath::Power(s/s_0r,eps2)*L;
    //Double_t A1 = a * L*L;
    //Double_t C1 = c * L*L;
    TComplex exp_term1(b * t / 2., 0.);
    TComplex exp_term2(d * t / 2., phi);
    //TComplex exp_term2( d*t/2. + sqrtbrake, phi );

    A = A1 * TComplex::Exp(exp_term1) + C1 * TComplex::Exp(exp_term2);

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
void PPdsdt::setSqrtS(double sqrtS) {
    this->_s = sqrtS;
}

/**
 * Get centre of mass energy
 * @return sqrt(s)
 */
double PPdsdt::getSqrtS() const {
    return _s;
}
