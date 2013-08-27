/*

 * dataset.h

 * 

 * 

 */



#ifndef DATASET_H
#define DATASET_H

#include <string>

class Dataset {
public:
    Dataset();
    
    explicit Dataset( const std::string& );
    
    virtual ~Dataset();

    /** Check compositeness of the object */
    virtual Dataset* getComposite();

    /** Add new data to the dataset */
    virtual void addDataset(Dataset* ds);

    /** Calculate chi2 of the dataset */
    virtual double computeChi2( const double* ) const;
    
    /** Print info about the dataset */
    virtual void print() const;
    
    /** Get numer of points in the dataset */
    virtual int nPoints() const;
    
    /** Set name of the dataset */
    void setName( const std::string& name);
    
    /** Get name of the dataset */
    std::string getName() const;

private:
    /** Dataset's name */
    std::string _name;
};

#endif /* DATASET_H */ 
