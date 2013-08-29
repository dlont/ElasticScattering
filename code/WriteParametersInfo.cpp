/* 
 * File:   WriteParametersInfo.cpp
 * Author: Інна_Денис
 * 
 * Created on 29 Август 2013 г., 21:35
 */

#include "WriteParametersInfo.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include "SigDig.h"

#include "TMath.h"

WriteParametersInfo::WriteParametersInfo() {
}

WriteParametersInfo::WriteParametersInfo(const WriteParametersInfo& orig) {
}

WriteParametersInfo::~WriteParametersInfo() {
}

void WriteParametersInfo::setMinimizer(ROOT::Math::Minimizer* minimizer) {
    this->_minimizer = minimizer;
}

void WriteParametersInfo::DumpFileCSV( double nPoints, const std::string& fileName, const std::vector<int>& paramIDs ) {
    if ( _minimizer == 0 ) {
        std::cout << "ERROR: Minimizer is not set:" << std::endl;
        return;
    }
    
    ofstream file(fileName);
    
    int nParams = _minimizer->NDim();
    const double *par = new double[ nParams ];
    const double *parErr = new double[ nParams ];
    par = _minimizer->X();
    parErr = _minimizer->Errors();
    double minChi2 = _minimizer->MinValue();
    int NfreeParam = _minimizer->NFree();
    double NDF = (nPoints - NfreeParam);
        
    file << "$\\chi^2$/NDF," << minChi2 / NDF << std::endl;
    
    std::vector<int>::const_iterator itrPar;
    for ( itrPar = paramIDs.begin(); itrPar != paramIDs.end(); ++itrPar ) {
        if (parErr[*itrPar] > 0.) { // Parameter was not fixed
            float rel_err = parErr[*itrPar] / par[*itrPar];
            file . setf(std::ios::left);
            file << "$" << _minimizer->VariableName(*itrPar) << "$" << ",";
            file . unsetf(std::ios::left);
            file << std::setw(20);
            file << std::fixed
                    << std::setprecision(abs(Order(parErr[*itrPar]) - Order(par[*itrPar])) + SigDig(parErr[*itrPar]) - 1);
            file << Result(par[*itrPar], parErr[*itrPar]) * TMath::Power(10., -Order(par[*itrPar])) << ",";
            file << std::setw(20);
            file << std::fixed;
            file << std::setprecision(abs(Order(parErr[*itrPar]) - Order(par[*itrPar])) + SigDig(parErr[*itrPar]) - 1)
                    << AbsErr(parErr[*itrPar])*(TMath::Power(10., Order(parErr[*itrPar]) - Order(par[*itrPar])));
            file << std::setw(10);
            if (Order(par[*itrPar]) == 0) file << "," << std::endl;
            else file << ", " << "$\\times 10^{" << Order(par[*itrPar]) << "}$" << std::endl;
        } else { // Parameter was fixed
            file . setf(std::ios::left);
            file << "$" << _minimizer->VariableName(*itrPar) << "$" << ",";
            file . unsetf(std::ios::left);
            file << std::setw(20);
            file << std::fixed
                    << par[*itrPar] << ",";
            file << std::setw(20);
            file << std::fixed;
            file << std::setprecision(1)
                    << "fixed";
            file << std::setw(10);
            file << "," << std::endl;
        }
    }
    file.close();
    return;
}

void WriteParametersInfo::DumpInitParametersInclude( const std::string& fileName ) {
    
    ofstream file( fileName );
    
    file<< "std::vector< std::pair< string, double > > ipar(NPARAMS);" << std::endl;
    int nParams = _minimizer->NDim();
    const double *par = new double[ nParams ];
    par = _minimizer->X();
    for ( int ipar = 0; ipar < nParams; ++ipar ) {
        file<< "ipar[" << ipar << "]  = std::make_pair(\"" << _minimizer->VariableName( ipar ) << "\", "<< par[ ipar ] << ");" << std::endl;
    }
    
    file.close();
    
    return;
}