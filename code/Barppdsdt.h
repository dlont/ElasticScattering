/*

 * barppdsdt.h

 *

 */



#ifndef BARPPDSDT_H
#define BARPPDSDT_H

#include "Functor.h"

class BarPPdsdt: public Functor
{
    public:
        BarPPdsdt();
        
        explicit BarPPdsdt( double sqrtS );
        
        virtual ~BarPPdsdt();

        virtual double operator() ( double* x, const double *par );

        /** Set seter of mass energy */
        void setSqrtS(double _sqrtS);
        
        /** get seter of mass energy */
        double getSqrtS() const;
    private:
        double _s;
        /* add your private declarations */
};

#endif /* BARPPDSDT_H */

