/* 
 * File:   TRangeCondition.h
 * Author: Інна_Денис
 *
 * Created on 26 Август 2013 г., 15:45
 */

#ifndef TRANGECONDITION_H
#define	TRANGECONDITION_H

#include "Utility.h"
#include "Condition.h"

#include <string>

class TRangeCondition : public Condition {
private:
    DISALLOW_COPY_AND_ASSIGN( TRangeCondition );
    
public:
    TRangeCondition();
    
    explicit TRangeCondition( const std::string& );
    
    TRangeCondition( const std::string&, double, double );
    
    virtual ~TRangeCondition();
    
    virtual void print() const;
    
    virtual bool isGood( double ) const;
    
private:

    /** Minimum allowed value of t */
    double _mint;
    
    /** Maximum allowed value of t */
    double _maxt;
};

#endif	/* TRANGECONDITION_H */

