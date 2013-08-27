/*

 * ppdsdt.h

 */



#ifndef PPDSDT_H
#define PPDSDT_H

#include "Functor.h"

class PPdsdt: public Functor
{
    public:
        PPdsdt();
        
        explicit PPdsdt( double sqrtS );
        
        virtual ~PPdsdt();

        virtual double operator() ( double* x, const double *par );
        
        /** Set seter of mass energy */
        void setSqrtS( double sqrtS );
        
        /** get seter of mass energy */
        double getSqrtS() const;

    private:
        double _s;
        /* add your private declarations */
};

#endif /* PPDSDT_H */
