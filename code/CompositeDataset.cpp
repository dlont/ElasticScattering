/*

 * compositedataset.cpp

 * 

 */



#include "CompositeDataset.h"


CompositeDataset::CompositeDataset() :
Dataset( "EmptyCompositeDataset" )
{
	
}

CompositeDataset::CompositeDataset( const std::string& name ) : 
Dataset( name )
{
    
}

CompositeDataset::~CompositeDataset()
{
	
}

/**
 * Check compositness of the dataset
 * @return this if the object is composite, 0 otherwise
 */
CompositeDataset* CompositeDataset::getComposite()
{
	return this;
}

/**
 * Add a dataset to the list of sets
 * @param ds
 */
void CompositeDataset::addDataset( Dataset* ds )
{
	_datasets.push_back( ds );
	
	return;
}

/**
 * Compute sum of chi2 contributions of all datasets
 * 
 * @return chi2
 */
double CompositeDataset::computeChi2( const double* par ) const
{
    double chi2 = 0.;
    
    // iterate over datasets
    std::list< Dataset* >::const_iterator itrDat;
    for ( itrDat = _datasets.begin(); itrDat != _datasets.end(); ++itrDat ) {
        chi2 += (*itrDat)->computeChi2( par );
    }
    
    return chi2;
    
}

/**
 * Compute number of points satisfying all restrictions
 * 
 * @return n points
 */
int CompositeDataset::nPoints( ) const 
{
    int npoints = 0.;
    
    // iterate over datasets
    std::list< Dataset* >::const_iterator itrDat;
    for ( itrDat = _datasets.begin(); itrDat != _datasets.end(); ++itrDat ) {
        npoints += (*itrDat)->nPoints( );
    }
    
    return npoints;
}

void CompositeDataset::print() const
{
    std::cout << "Composite dataset:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "N points: " << nPoints() << std::endl;
    std::cout << "dataset includes:" << std::endl;
    std::list< Dataset* >::const_iterator itrDat;
    for ( itrDat = _datasets.begin(); itrDat != _datasets.end(); ++itrDat ) {
        (*itrDat)->print();
    }
}
