/* 
 * File:   DatasetPPtot.cpp
 * Author: Інна_Денис
 * 
 * Created on 30 Август 2013 г., 10:13
 */

#include "DatasetPPtot.h"
#include "Dataset.h"
#include "TGraph.h"
#include "Functor.h"
#include "Condition.h"

#include <iostream>

DatasetPPtot::DatasetPPtot():
Dataset(),
_pptotGraph(0),
_pptotModel(0),
_condition(0)
{
}

DatasetPPtot::DatasetPPtot(const string& name):
Dataset(name),
_pptotGraph(0),
_pptotModel(0),
_condition(0)
{
}

DatasetPPtot::~DatasetPPtot() {
    delete _pptotModel;
}

double DatasetPPtot::computeChi2( const double* par ) const {
    double chi2 = 0.;

    if ( !_pptotGraph ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Dataset: " << Dataset::getName() << std::endl;
        std::cout << "Can't calculate chi2!" << std::endl;
        std::cout << "Graph was not specified" << std::endl;
    }
    
    double tmp = 0.;
    int startBin = 1;
    int finishBin = _pptotGraph->GetN();
    double x[ NDIM ];
    for (int ix = startBin; ix < finishBin; ++ix) {
        x[0] = _pptotGraph->GetX()[ix];
        if ( _condition != 0 ) {
            if ( !_condition->isGood( x[0] ) ) continue;
        }
        if (_pptotGraph->GetErrorY(ix) > 0.) {
            tmp = (_pptotGraph->GetY()[ix] - (*_pptotModel)(x, par)) / (_pptotGraph->GetErrorY(ix));
            chi2 += tmp*tmp;
        }
    }

    return chi2;
}

/**
 * Set dataset graph object
 * @param gr
 */
void DatasetPPtot::setGraph(TGraph* gr) {
    this->_pptotGraph = gr;
}

/**
 * Get dataset graph object
 * @return dataset's graph
 */
TGraph* DatasetPPtot::getGraph() const {
    return _pptotGraph;
}

/**
 * Set model describing this dataset
 * @param model
 */
void DatasetPPtot::setModel( Functor* model) {
    this->_pptotModel = model;
}

/**
 * Get model object
 * @return model's functor
 */
Functor* DatasetPPtot::getModel() const {
    return _pptotModel;
}

void DatasetPPtot::print() const
{
    std::cout << "Dataset:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "N points: " << nPoints() << std::endl;
    std::cout << "Graph" << std::endl;
    _pptotGraph->Print();
}

int DatasetPPtot::nPoints() const
{
    int nPoints = 0.;

    if ( !_pptotGraph ) {
        std::cout << "ERROR!!!" << std::endl;
        std::cout << "Dataset: " << Dataset::getName() << std::endl;
        std::cout << "Can't calculate npoints!" << std::endl;
        std::cout << "Graph was not specified" << std::endl;
    }
    
    int startBin = 1;
    int finishBin = _pptotGraph->GetN();
    double x[ NDIM ];
    for (int ix = startBin; ix < finishBin; ++ix) {
        x[0] = _pptotGraph->GetX()[ix];
        if ( _condition != 0 ) {
            if ( !_condition->isGood( x[0] ) ) continue;
        }
        if (_pptotGraph->GetErrorY(ix) > 0.) {
            nPoints++;
        }
    }

    return nPoints;
}

void DatasetPPtot::setCondition(Condition* _condition) {
    this->_condition = _condition;
}

Condition* DatasetPPtot::getCondition() const {
    return _condition;
}
