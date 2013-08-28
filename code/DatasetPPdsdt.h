/* 
 * File:   datasetPPdsdt.h
 * Author: Інна_Денис
 *
 * Created on 25 Август 2013 г., 20:06
 */

#ifndef DATASETPPDSDT_H
#define	DATASETPPDSDT_H

#include "Dataset.h"
#include "Utility.h"

class Functor;
class Condition;
class TGraph;

/**
 * @class DatasetPPdsdt
 * 
 * Dataset object describing 
 * PP single differential ds/dt cross section 
 */
class DatasetPPdsdt : public Dataset {
private:
    DISALLOW_COPY_AND_ASSIGN( DatasetPPdsdt );
        
public:
    DatasetPPdsdt();
    
    explicit DatasetPPdsdt( double );
    
    DatasetPPdsdt( const std::string& name, double sqrtS = 1. );
    
    virtual ~DatasetPPdsdt();
    
    /** Calculate chi2 of the dataset */
    double computeChi2( const double* ) const;
    
    /** Set dataset graph object */
    void setGraph( TGraph* );
    
    /** Get dataset graph object */
    TGraph* getGraph() const;
    
    /** Set single differential cross section formula */
    void setModel( Functor* _ppdsdtModel);
    
    /** Get model object */
    Functor* getModel() const;
    
    /** Set seter of mass energy */
    void setSqrtS( double sqrtS );
        
    /** get seter of mass energy */
    double getSqrtS() const;
    
    /** Print info about the dataset */
    virtual void print() const;
    
    /** Get numer of points in the dataset */
    virtual int nPoints() const;
    
    /** Specifify condition on datapoints */
    void setCondition(Condition* _condition);
    
    /** Retrieve condition on datapoints */
    Condition* getCondition() const;
    
private:

    /** Dataset's ds/dt graph */
    TGraph* _ppdsdtGraph;
    
    /** Model describing ds/dt cross section */
    Functor* _ppdsdtModel;
    
    /** Chi2 evaluation condition */
    Condition* _condition;
    
    /** Centre of mass energy */
    double _s;

};

#endif	/* DATASETPPDSDT_H */

