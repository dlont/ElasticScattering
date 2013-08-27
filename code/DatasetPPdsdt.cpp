/* 
 * File:   datasetPPdsdt.cpp
 * Author: Інна_Денис
 * 
 * Created on 25 Август 2013 г., 20:07
 */

#include "DatasetPPdsdt.h"
#include "Dataset.h"
#include "PPdsdt.h"
#include "Utility.h"

#include "TGraph.h"
#include "TGraphErrors.h"
#include "Condition.h"

#include <iostream>

DatasetPPdsdt::DatasetPPdsdt() :
Dataset(),
_ppdsdtGraph(0),
_ppdsdtModel(0),
_condition(0),
_s(-1.) {
    _ppdsdtModel = new PPdsdt();
}

DatasetPPdsdt::DatasetPPdsdt( double sqrtS ) :
Dataset(),
_ppdsdtGraph(0),
_ppdsdtModel(0),
_condition(0),
_s(sqrtS) {
    _ppdsdtModel = new PPdsdt();
    setSqrtS( sqrtS );
}

DatasetPPdsdt::DatasetPPdsdt( const std::string& name, double sqrtS ) :
Dataset( name ),
_ppdsdtGraph(0),
_ppdsdtModel(0),
_condition(0),
_s(sqrtS) {
    _ppdsdtModel = new PPdsdt();
    setSqrtS( sqrtS );
}

DatasetPPdsdt::~DatasetPPdsdt() {
    delete _ppdsdtModel;
}

double DatasetPPdsdt::computeChi2( const double* par ) const {
    double chi2 = 0.;

    if ( !_ppdsdtGraph ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Dataset: " << Dataset::getName() << std::endl;
        std::cout << "Can't calculate chi2!" << std::endl;
        std::cout << "Graph was not specified" << std::endl;
    }
    
    double tmp = 0.;
    int startBin = 1;
    int finishBin = _ppdsdtGraph->GetN();
    double x[ NDIM ];
    for (int ix = startBin; ix < finishBin; ++ix) {
        x[0] = _ppdsdtGraph->GetX()[ix];
        if ( _condition != 0 ) {
            if ( !_condition->isGood( x[0] ) ) continue;
        }
        if (_ppdsdtGraph->GetErrorY(ix) > 0.) {
            tmp = (_ppdsdtGraph->GetY()[ix] - (*_ppdsdtModel)(x, par)) / (_ppdsdtGraph->GetErrorY(ix));
            chi2 += tmp*tmp;
        }
    }

    return chi2;
}

/**
 * Set dataset graph object
 * @param gr
 */
void DatasetPPdsdt::setGraph(TGraph* gr) {
    this->_ppdsdtGraph = gr;
}

/**
 * Get dataset graph object
 * @return dataset's graph
 */
TGraph* DatasetPPdsdt::getGraph() const {
    return _ppdsdtGraph;
}

/**
 * Set model describing this dataset
 * @param model
 */
void DatasetPPdsdt::setModel(Functor* model) {
    this->_ppdsdtModel = model;
}

/**
 * Get model object
 * @return model's functor
 */
Functor* DatasetPPdsdt::getModel() const {
    return _ppdsdtModel;
}

/**
 * Set centre of mass energy
 * @param sqrtS centre of mass energy
 */
void DatasetPPdsdt::setSqrtS(double s) {
    this->_s = s;
    static_cast<PPdsdt*>(_ppdsdtModel)->setSqrtS( this->_s );
}

/**
 * Get centre of mass energy
 * @return sqrt(s)
 */
double DatasetPPdsdt::getSqrtS() const {
    return _s;
}

void DatasetPPdsdt::print() const
{
    std::cout << "Dataset:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "N points: " << nPoints() << std::endl;
    std::cout << "sqrt(s): " << sqrt(this->_s) << std::endl;
    std::cout << "Graph" << std::endl;
    _ppdsdtGraph->Print();
}

int DatasetPPdsdt::nPoints() const
{
    int nPoints = 0.;

    if ( !_ppdsdtGraph ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Dataset: " << Dataset::getName() << std::endl;
        std::cout << "Can't calculate npoints!" << std::endl;
        std::cout << "Graph was not specified" << std::endl;
    }
    
    int startBin = 1;
    int finishBin = _ppdsdtGraph->GetN();
    double x[ NDIM ];
    for (int ix = startBin; ix < finishBin; ++ix) {
        x[0] = _ppdsdtGraph->GetX()[ix];
        if ( _condition != 0 ) {
            if ( !_condition->isGood( x[0] ) ) continue;
        }
        if (_ppdsdtGraph->GetErrorY(ix) > 0.) {
            nPoints++;
        }
    }

    return nPoints;
}

void DatasetPPdsdt::setCondition(Condition* _condition) {
    this->_condition = _condition;
}

Condition* DatasetPPdsdt::getCondition() const {
    return _condition;
}
