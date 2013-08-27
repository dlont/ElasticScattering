/*

 * functor.h

 * 

 */



#ifndef FUNCTOR_H
#define FUNCTOR_H

#include <string>

class Functor {
public:
    Functor();
    explicit Functor( const std::string& );
    virtual ~Functor();

    virtual double operator() (double* x, const double* p) = 0;
    
    void setName( const std::string& name );
    
    std::string getName() const;

private:
    /** Dataset's name */
    std::string _name;
    /* add your private declarations */
};

#endif /* FUNCTOR_H */ 
