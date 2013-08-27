/*
 * chi2object.h
 * 
 */


#ifndef CHI2OBJECT_H
#define CHI2OBJECT_H

#include "Utility.h"

#include <vector>
#include <map>
#include <string>

class Dataset;

class TGraphErrors;

class Chi2Object {
public:
    /** Constructor */
    Chi2Object();

    /** Destructor */
    virtual ~Chi2Object();

    /** Calculate total Chi2 */
    double operator()(const double*) const;

    void setDataSetsDSigmaDtPPBar(Dataset* _dataSetsDSigmaDtPPBar);

    Dataset* getDataSetsDSigmaDtPPBar() const;

    void setDataSetsDSigmaDtPP(Dataset* _dataSetsDSigmaDtPP);

    Dataset* getDataSetsDSigmaDtPP() const;

    void setDataSetsRhoPPBar(Dataset* _dataSetsRhoPPBar);

    Dataset* getDataSetsRhoPPBar() const;

    void setDataSetsRhoPP(Dataset* _dataSetsRhoPP);

    Dataset* getDataSetsRhoPP() const;

    void setDataSetsSigmaTotPPBar(Dataset* _dataSetsSigmaTotPPBar);

    Dataset* getDataSetsSigmaTotPPBar() const;

    void setDataSetsSigmaTotPP(Dataset* _dataSetsSigmaTotPP);

    Dataset* getDataSetsSigmaTotPP() const;
    
    int getNPoints() const;
    

private:
    /** Contribution to the Chi2 of the total PP cross section */
    double chi2SigmaTotPP(double *par);

    /** Contribution to the Chi2 of the total PPbar cross section */
    double chi2SigmaTotPPBar(double *par);

    /** Contribution to the Chi2 of the Rho PP function */
    double chi2RhoPP(double *par);

    /** Contribution to the Chi2 of the Rho PPbar function */
    double chi2RhoPPBar(double *par);

    /** Contribution to the Chi2 of the differential ds/dt PP cross section */
    double chi2DsigmaDtPP(double *par);

    /** Contribution to the Chi2 of the differential ds/dt PPbar cross section */
    double chi2DsigmaDtPPBar(double *par);


private:
    /** Total PP cross section graphs */
    Dataset* _dataSetsSigmaTotPP;

    /** Total PPbar cross section graphs */
    Dataset* _dataSetsSigmaTotPPBar;

    /** Rho PP function graphs */
    Dataset* _dataSetsRhoPP;

    /** Rho PPbar function graphs */
    Dataset* _dataSetsRhoPPBar;

    /** PP differential ds/dt cross section graphs */
    Dataset* _dataSetsDSigmaDtPP;

    /** PPbar differential ds/dt cross section graphs */
    Dataset* _dataSetsDSigmaDtPPBar;

public:
    bool _useTotalCS;
    bool _useRho;
    bool _useDifferentialCS;

private:
    mutable int _nPoints;
};

#endif /* CHI2OBJECT_H */ 

