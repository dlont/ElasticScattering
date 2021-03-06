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

    explicit PPdsdtTdependentPhase(double);

    virtual ~PPdsdtTdependentPhase();

    virtual double operator() (double* x, const double *par);

    /** Set seter of mass energy */
    void setSqrtS(double sqrtS);

    /** get seter of mass energy */
    double getSqrtS() const;
    
    void setScale(double);
    
    double getScale() const;

private:
    /** Center of mass energy */
    double _s;
    /** Function scale factor, used for plotting purposes */
    double _scale;
    /* add your private declarations */

};

#endif	/* PPDSDTTDEPENDENTPHASE_H */

