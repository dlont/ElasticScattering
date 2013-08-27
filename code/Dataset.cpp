/*

 * dataset.cpp

 * 

 */


#include "Dataset.h"

#include <string>
#include <iostream>

Dataset::Dataset() :
_name("EmptyDataset")
{
	
}

Dataset::Dataset( const std::string& name) :
_name(name)
{
	
}

Dataset::~Dataset()
{
	
}

/**
 * Virtual member to be implemented by user.
 * Check compositness of the dataset. 
 * @return 0 as a sign that the object is not a composition
 */
Dataset* Dataset::getComposite()
{
	return 0;
}

/**
 * Virtual member to be implemented by user.
 * Addition of the dataset to the list.
 * @param ds
 */
void Dataset::addDataset( Dataset* ds )
{
	return;
}

/**
 * Compute chi2 contribution
 * 
 * @return chi2
 */
double Dataset::computeChi2( const double* par ) const
{
    return 0.;
}

/**
 * Compute number of points satisfying all restrictions
 * 
 * @return n points
 */
int Dataset::nPoints( ) const 
{
    return 0;
}

/**
 * Print info about the dataset
 */
void Dataset::print() const 
{
    std::cout << "Dataset:" << std::endl;
    std::cout << "Name: " << this->_name;
    std::cout << "N points: " << nPoints();
}

/**
 * Sate name of the dataset
 * @param name
 */
void Dataset::setName( const std::string& name) {
    this->_name = name;
}

/**
 * Get name of the dataset
 * @return name
 */
std::string Dataset::getName() const {
    return _name;
}
