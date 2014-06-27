/* 
 * File:   context_aware.h
 * Author: daniele
 *
 * Created on 27 giugno 2014, 10.13
 */

#ifndef CONTEXT_AWARE_H
#define	CONTEXT_AWARE_H

#include "subscribe.h"

typedef void (*function_pointer)();

/**
 * Generic class for context awareness
 * @param sub : publish-subscribe implementation
 */
class ContextAware{
public:
    ContextAware(subscribe& sub);
    virtual ~ContextAware();
    
    /**
     * Register to the context aware implementation
     * @param x
     * @param 
     * @return 
     */
    bool registration(TRIGGER_rule::rules x, function_pointer);
    
    
    /**
     * Unregister to the context aware implementation
     * @param 
     * @return 
     */
    bool unregistration(function_pointer);
    
    /**
     * Get the measure of the context aware implementation
     * @return 
     */
    virtual double getMeasure() = 0;

protected:
    subscribe& _sub;
    
    
private:
    ContextAware(const ContextAware& orig);
    
    
};



#endif	/* CONTEXT_AWARE_H */

