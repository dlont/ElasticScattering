/* 
 * File:   WriteParametersInfo.h
 * Author: Інна_Денис
 *
 * Created on 29 Август 2013 г., 21:35
 */

#ifndef WRITEPARAMETERSINFO_H
#define	WRITEPARAMETERSINFO_H

#include "Math/Minimizer.h"

class WriteParametersInfo {
public:
    WriteParametersInfo();
    
    WriteParametersInfo(const WriteParametersInfo& orig);
    
    virtual ~WriteParametersInfo();
    
    void DumpFileCSV( double, const std::string&, const std::vector<int>&);
    
    void DumpInitParametersInclude( const std::string& );
    
    void setMinimizer(ROOT::Math::Minimizer* _minimizer);
    
private:
        ROOT::Math::Minimizer* _minimizer;
};

#endif	/* WRITEPARAMETERSINFO_H */

