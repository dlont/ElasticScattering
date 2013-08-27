/*

 * compositedataset.h

 * 

 */


#ifndef COMPOSITEDATASET_H
#define COMPOSITEDATASET_H

#include <list>
#include <iostream>

#include "Dataset.h"

class CompositeDataset : public Dataset {
public:
    CompositeDataset();
    
    explicit CompositeDataset( const std::string& name );
    
    virtual ~CompositeDataset();

    /** Check compositeness of the object */
    virtual CompositeDataset* getComposite();

    /** Add new data to the dataset */
    virtual void addDataset(Dataset* ds);

    /** Calculate chi2 of the dataset */
    virtual double computeChi2( const double* ) const;

    /** Print info about the dataset */
    virtual void print() const;
    
    /** Get numer of points in the dataset */
    virtual int nPoints() const;
    
private:
    std::list< Dataset* > _datasets;
};

#endif /* COMPOSITEDATASET_H */ 
