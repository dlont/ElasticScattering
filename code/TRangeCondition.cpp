/* 
 * File:   TRangeCondition.cpp
 * Author: Інна_Денис
 * 
 * Created on 26 Август 2013 г., 15:45
 */

#include "TRangeCondition.h"

#include <iostream>

TRangeCondition::TRangeCondition() : 
Condition("EmptyTRangeCondition"),
_mint(-1.),
_maxt(-1)
{
    
}

TRangeCondition::TRangeCondition( const std::string& name ) :
Condition(name),
_mint(-1.),
_maxt(-1)
{
    
}

TRangeCondition::TRangeCondition( const std::string& name, double min, double max ) :
Condition(name),
_mint(min),
_maxt(max)
{
    
}

TRangeCondition::~TRangeCondition() {
}

void TRangeCondition::print() const 
{
    std::cout << "Condition (t range) :" << std::endl;
    std::cout << Condition::getName() << std::endl;
    std::cout << "Min t: " << _mint << std::endl;
    std::cout << "Max t: " << _maxt << std::endl;
}

bool TRangeCondition::isGood( double t ) const {
    bool isGood = true;
    if ( t < _mint || t > _maxt ) isGood = false;
    
    return isGood;
}