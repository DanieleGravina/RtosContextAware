/* 
 * File:   subscribe.h
 * Author: nando
 *
 * Created on June 27, 2014, 10:44 AM
 */

#ifndef SUBSCRIBE_H
#define	SUBSCRIBE_H

typedef void (*function_pointer)();

class TRIGGER_rule{
public:
    enum rules
    {
        IN_OUT,
        OUT_IN 
    };
private:
    TRIGGER_rule();
};

class subscribe{
public:
    
    virtual bool record(TRIGGER_rule::rules x, function_pointer) = 0;
    virtual bool unrecord(function_pointer) = 0;
    virtual void change (bool y) = 0;
    
    
     virtual ~subscribe(){}
    
    
};

#endif	/* SUBSCRIBE_H */

