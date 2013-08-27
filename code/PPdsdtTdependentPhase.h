/* 
 * File:   PPdsdtTdependentPhase.h
 * Author: Інна_Денис
 *
 * Created on 27 Август 2013 г., 23:00
 */

#ifndef PPDSDTTDEPENDENTPHASE_H
#define	PPDSDTTDEPENDENTPHASE_H

#include "Functor.h"

class PPdsdtTdependentPhase : public Functor {
public:
    PPdsdtTdependentPhase();

    PPdsdtTdependentPhase(const PPdsdtTdependentPhase& orig);

    virtual ~PPdsdtTdependentPhase();

    virtual double operator() (double* x, const double *par);

    /** Set seter of mass energy */
    void setSqrtS(double sqrtS);

    /** get seter of mass energy */
    double getSqrtS() const;

private:
    double _s;
    /* add your private declarations */

};

#endif	/* PPDSDTTDEPENDENTPHASE_H */

