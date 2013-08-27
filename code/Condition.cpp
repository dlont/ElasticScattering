/* 
 * File:   Condition.cpp
 * Author: Інна_Денис
 * 
 * Created on 26 Август 2013 г., 15:28
 */

#include "Condition.h"

#include <iostream>
#include <string>

Condition::Condition() :
_name("EmptyCondition")
{
}

/**
 * Virtual member to be implemented by user.
 * Check compositness of the condition. 
 * @return 0 as a sign that the object is not a composition
 */
Condition* Condition::getComposite()
{
	return 0;
}

/**
 * Virtual member to be implemented by user.
 * Addition of the condition to the list.
 * @param ds
 */
void Condition::addCondition( Condition* ds )
{
	return;
}

void Condition::print() const 
{
    std::cout << "Condtion:" << std::endl;
    std::cout << _name << std::endl;
}

bool Condition::isGood() const 
{
    return true;
}

bool Condition::isGood( double x) const 
{
    return true;
}

void Condition::setName(const std::string& name) {
    this->_name = name;
}

std::string Condition::getName() const {
    return _name;
}

Condition::Condition(const std::string& name) :
_name(name)
{
}

Condition::~Condition() {
}

