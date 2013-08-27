/*
 * chi2object.cpp
 * 
 * 
 */


#include "Chi2Object.h"
#include "Dataset.h"

#include "TGraphErrors.h"

#include <iostream>

Chi2Object::Chi2Object() :
_dataSetsSigmaTotPP(0),
_dataSetsSigmaTotPPBar(0),
_dataSetsRhoPP(0),
_dataSetsRhoPPBar(0),
_dataSetsDSigmaDtPP(0),
_dataSetsDSigmaDtPPBar(0),
_useTotalCS(false),
_useRho(false),
_useDifferentialCS(false),
_nPoints(0) {

}

Chi2Object::~Chi2Object() {

}

void Chi2Object::setDataSetsDSigmaDtPPBar(Dataset* ds) {
    this->_dataSetsDSigmaDtPPBar = ds;
}

Dataset* Chi2Object::getDataSetsDSigmaDtPPBar() const {
    return _dataSetsDSigmaDtPPBar;
}

void Chi2Object::setDataSetsDSigmaDtPP(Dataset* ds) {
    this->_dataSetsDSigmaDtPP = ds;
}

Dataset* Chi2Object::getDataSetsDSigmaDtPP() const {
    return _dataSetsDSigmaDtPP;
}

void Chi2Object::setDataSetsRhoPPBar(Dataset* ds) {
    this->_dataSetsRhoPPBar = ds;
}

Dataset* Chi2Object::getDataSetsRhoPPBar() const {
    return _dataSetsRhoPPBar;
}

void Chi2Object::setDataSetsRhoPP(Dataset* ds) {
    this->_dataSetsRhoPP = ds;
}

Dataset* Chi2Object::getDataSetsRhoPP() const {
    return _dataSetsRhoPP;
}

void Chi2Object::setDataSetsSigmaTotPPBar(Dataset* ds) {
    this->_dataSetsSigmaTotPPBar = ds;
}

Dataset* Chi2Object::getDataSetsSigmaTotPPBar() const {
    return _dataSetsSigmaTotPPBar;
}

void Chi2Object::setDataSetsSigmaTotPP(Dataset* ds) {
    this->_dataSetsSigmaTotPP = ds;
}

Dataset* Chi2Object::getDataSetsSigmaTotPP() const {
    return _dataSetsSigmaTotPP;
}

int Chi2Object::getNPoints() const {
    
    int npoints = 0;

    if ( _useDifferentialCS ) {
        npoints    += !_dataSetsDSigmaDtPP    ? 0. : _dataSetsDSigmaDtPP->nPoints();
        npoints    += !_dataSetsDSigmaDtPPBar ? 0. : _dataSetsDSigmaDtPPBar->nPoints();
    }

    if ( _useTotalCS ) {
        npoints    += !_dataSetsSigmaTotPP    ? 0. : _dataSetsSigmaTotPP->nPoints();
        npoints    += !_dataSetsSigmaTotPPBar ? 0. : _dataSetsSigmaTotPPBar->nPoints();
    }
    
    if ( _useRho ) {
        npoints    += !_dataSetsRhoPP         ? 0. : _dataSetsRhoPP->nPoints();
        npoints    += !_dataSetsRhoPPBar      ? 0. : _dataSetsRhoPPBar->nPoints();
    }

    this->_nPoints = npoints;
    
    return _nPoints;
}

/** Chi2 calculation operator 
 * 
 * @param par parameters values
 * @return chi2
 * 
 * */
double Chi2Object::operator()(const double* par) const {

    double chi2 = 0.; // total chi2

    double chi2DsDtPP = 0.;
    double chi2DsDtPPBar = 0.;
    if ( _useDifferentialCS ) {
        chi2DsDtPP    = !_dataSetsDSigmaDtPP    ? 0. : _dataSetsDSigmaDtPP->computeChi2(par);
        chi2DsDtPPBar = !_dataSetsDSigmaDtPPBar ? 0. : _dataSetsDSigmaDtPPBar->computeChi2(par);
    }
    double chi2TotPP = 0.;
    double chi2TotPPBar = 0.;
    if ( _useTotalCS ) {
        chi2TotPP    = !_dataSetsSigmaTotPP    ? 0. : _dataSetsSigmaTotPP->computeChi2(par);
        chi2TotPPBar = !_dataSetsSigmaTotPPBar ? 0. : _dataSetsSigmaTotPPBar->computeChi2(par);
    }
    double chi2RhoPP = 0.;
    double chi2RhoPPBar = 0.;
    if ( _useRho ) {
        chi2RhoPP    = !_dataSetsRhoPP ? 0. : _dataSetsRhoPP->computeChi2(par);
        chi2RhoPPBar = !_dataSetsRhoPPBar ? 0. : _dataSetsRhoPPBar->computeChi2(par);
    }

    chi2 += chi2DsDtPP;
    chi2 += chi2DsDtPPBar;
    chi2 += chi2TotPP;
    chi2 += chi2TotPPBar;
    chi2 += chi2RhoPP;
    chi2 += chi2RhoPPBar;
    
    return chi2;
}

