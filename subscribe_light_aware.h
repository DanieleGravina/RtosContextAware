/* 
 * File:   subscribe.h
 * Author: nando
 *
 * Created on May 30, 2014, 11:40 AM
 */

#ifndef SUBSCRIBE_LIGHT_AWARE_H
#define	SUBSCRIBE_LIGHT_AWARE_H

#include <vector>
#include <list>
#include "miosix/miosix.h"
#include <pthread.h>
#include <subscribe.h>
#include <cstdio>

using namespace std;
using namespace miosix;

class subscribe_light_aware : public subscribe{
public:
    subscribe_light_aware();
    virtual ~subscribe_light_aware();
    
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
    
    
    
 
private:
    bool state=false;
    TRIGGER_rule::rules trans;
    std::list<function_pointer> clients_INOUT;
    std::list<function_pointer> clients_OUTIN; 
    pthread_t t1;
    bool firstCall;
    
    pthread_mutex_t mutexList;
    pthread_mutex_t mutexHandler;

    
protected:
    /**
    */
   void *handler();
    
   static void *handler_helper(void *context){
       
        return ((subscribe_light_aware *)context)->handler();
   }


};

#endif	/* SUBSCRIBE_H */

