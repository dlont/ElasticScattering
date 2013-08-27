/* 
 * File:   CompositeCondition.h
 * Author: Інна_Денис
 *
 * Created on 26 Август 2013 г., 16:00
 */

#ifndef COMPOSITECONDITION_H
#define	COMPOSITECONDITION_H

#include "Condition.h"

#include "Utility.h"

#include <string>
#include <vector>

class CompositeCondition : public Condition {
public:
    CompositeCondition();
    explicit CompositeCondition( const std::string& );
    virtual ~CompositeCondition();
    
    /** Check compositeness of the object */
    virtual CompositeCondition* getComposite();
    
    /** Add new data to the conditions */
    virtual void addCondition( Condition* cond );
    
    virtual void print() const;
    
    virtual bool isGood( double t ) const;
    
private:
    std::vector< Condition* > _subConditions;
};

#endif	/* COMPOSITECONDITION_H */

