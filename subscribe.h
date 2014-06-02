/* 
 * File:   subscribe.h
 * Author: nando
 *
 * Created on May 30, 2014, 11:40 AM
 */

#ifndef SUBSCRIBE_H
#define	SUBSCRIBE_H

#include <vector>
#include <list>
#include "miosix/miosix.h"

using namespace std;
using namespace miosix;

typedef void (*function_pointer)();

/*
 * Trigger rules used to get which kind of transaction we had
 * */

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

class subscribe {
public:
    subscribe();
    subscribe(const subscribe& orig);
    virtual ~subscribe();
    
    /**
     Allows user to register own function to an change event
     @param trigger rules
     @param pointer to function
     @return status of register*/

    bool record(TRIGGER_rule::rules x, function_pointer);
    
    /**
     Deallocate a subscription
     @param pointer to function
     @return true if the element is found and deleted otherwise false*/
    bool unrecord(function_pointer);
    
    /**
     Called by light_aware manager when occurred a transaction of environment
     @param toggle variable*/
    void change (bool y);
    
    void setState(bool x);
    bool getState();
   
    std::list<function_pointer> getClientsINOUT();
    std::list<function_pointer> getClientsOUTIN();

    void setTrans(TRIGGER_rule::rules x);
    
    TRIGGER_rule::rules getTrans();
    
    void addFunction(function_pointer f);
    void removeFunction(function_pointer f);
    
    /**
    */
    void handler(TRIGGER_rule::rules x);
    
 
private:
    bool state;
    TRIGGER_rule::rules trans;
    std::list<function_pointer> clients_INOUT;
    std::list<function_pointer> clients_OUTIN;    

};

#endif	/* SUBSCRIBE_H */

