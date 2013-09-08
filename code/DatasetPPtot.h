/* 
 * File:   DatasetPPtot.h
 * Author: Інна_Денис
 *
 * Created on 30 Август 2013 г., 10:13
 */

#ifndef DATASETPPTOT_H
#define	DATASETPPTOT_H

#include "Dataset.h"
#include "Utility.h"

class Functor;
class Condition;
class TGraph;

class DatasetPPtot : public Dataset {
private:
    DISALLOW_COPY_AND_ASSIGN( DatasetPPtot );
        
public:
    DatasetPPtot();
    
    explicit DatasetPPtot( const std::string& name );
    
    virtual ~DatasetPPtot();
    
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
    
    /** Print info about the dataset */
    virtual void print() const;
    
    /** Get numer of points in the dataset */
    virtual int nPoints() const;
    
    /** Specifify condition on datapoints */
    void setCondition(Condition* _condition);
    
    /** Retrieve condition on datapoints */
    Condition* getCondition() const;
    
private:

    /** Dataset's sig_tot graph */
    TGraph* _pptotGraph;
    
    /** Model describing sig_tot cross section */
    Functor* _pptotModel;
    
    /** Chi2 evaluation condition */
    Condition* _condition;
private:

};

#endif	/* DATASETPPTOT_H */

