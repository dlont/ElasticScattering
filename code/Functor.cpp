/*

 * functor.cpp

 * 

 */



#include "Functor.h"


Functor::Functor() :
_name("EmptyFunctor")
{
	
}

void Functor::setName( const std::string& name) {
    this->_name = name;
}

std::string Functor::getName() const {
    return _name;
}

Functor::Functor(const std::string& name) : _name(name)
{
    
}

Functor::~Functor()
{
	
}

