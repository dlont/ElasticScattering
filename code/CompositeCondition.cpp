/* 
 * File:   CompositeCondition.cpp
 * Author: Інна_Денис
 * 
 * Created on 26 Август 2013 г., 16:00
 */

#include "CompositeCondition.h"

#include <string>
#include <vector>
#include <iostream>

CompositeCondition::CompositeCondition() :
Condition("EmptyCompositeCondition"),
_subConditions()
{
}

CompositeCondition::CompositeCondition( const std::string& name ) :
Condition(name),
_subConditions()
{
}

CompositeCondition::~CompositeCondition() {
}

/**
 * Check compositness of the dataset
 * @return this if the object is composite, 0 otherwise
 */
CompositeCondition* CompositeCondition::getComposite()
{
	return this;
}

/**
 * Add a condition to the list of sets
 * @param cond
 */
void CompositeCondition::addCondition( Condition* cond )
{
	_subConditions.push_back( cond );
	
	return;
}

void CompositeCondition::print() const 
{
    std::cout << "Composite condition:" << std::endl;
    std::cout << Condition::getName() << std::endl;
    std::cout << "Condition consists of:" << std::endl;
    std::vector< Condition* >::const_iterator itrCond;
    for ( itrCond = _subConditions.begin(); itrCond != _subConditions.end(); ++itrCond ) {
        (*itrCond)->print();
    }
}

bool CompositeCondition::isGood( double t ) const {
    bool isGood = true;
    std::vector< Condition* >::const_iterator itrCond;
    for ( itrCond = _subConditions.begin(); itrCond != _subConditions.end(); ++itrCond ) {
        if ( !(*itrCond)->isGood(t) ) {
            isGood = false;
            break;
        }
    }
    
    return isGood;
}