/* 
 * File:   PPtot.h
 * Author: Інна_Денис
 *
 * Created on 30 Август 2013 г., 11:23
 */

#ifndef PPTOT_H
#define	PPTOT_H

#include "Functor.h"

class PPtot : public Functor{
public:
    PPtot();

    virtual ~PPtot();
    
    virtual double operator() (double* x, const double *par);

    void setScale(double);
    
    double getScale() const;

private:
    /** Function scale factor, used for plotting purposes */
    double _scale;
    /* add your private declarations */

};

#endif	/* PPTOT_H */

