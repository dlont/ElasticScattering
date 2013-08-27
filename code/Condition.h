/* 
 * File:   Condition.h
 * Author: Інна_Денис
 *
 * Created on 26 Август 2013 г., 15:28
 */

#ifndef CONDITION_H
#define	CONDITION_H

#include "Utility.h"

#include <string>

class Condition {
private:
    DISALLOW_COPY_AND_ASSIGN(Condition);
public:
    Condition();
    explicit Condition( const std::string& );
    virtual ~Condition();
    
    /** Check compositeness of the object */
    virtual Condition* getComposite();
    
    /** Add new data to the conditions */
    virtual void addCondition( Condition* );
    
    /** Print condition info */
    virtual void print() const;
    
    /** Check if condition is sattisfied */
    virtual bool isGood() const;
    
    /** Check if condition is sattisfied */
    virtual bool isGood( double ) const;
    
    void setName( const std::string& );
    
    std::string getName() const;
private:

    /** Name of the condition */
    std::string _name;
};

#endif	/* CONDITION_H */

