/* 
 * File:   subscribe.h
 * Author: nando
 *
 * Created on June 27, 2014, 10:44 AM
 */

#ifndef SUBSCRIBE_H
#define	SUBSCRIBE_H

typedef void (*function_pointer)();

/**
 * Wrapped class used to define a trigger rule about light context
 * IN_OUT when we have a transaction between outdoor environment and indoor one.
 * OUT_IN the viceversa.
 *
 */

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
/**
 * Abstract class that define a mandatory methods for subscribe class 
 * development for specific context aware class
 */
class subscribe{
public:
    
    /**
     * Allows the user to register own function for a specific event, that is mapped by trigger rule
     * @param x trigger rule
     * @param pointer to function
     * @return true if function is recorded otherwise false
     */
    virtual bool record(TRIGGER_rule::rules x, function_pointer) = 0;
    
    /**
     * Allows the user to delete own function recorded in the subscribe list
     * @param pointer function
     * @return true if function is deleted from subscribe list otherwise false
     */
    virtual bool unrecord(function_pointer) = 0;
    
    /**
     * Used by your context aware class to warn that some change occurred
     * @param y
     */
    virtual void change (bool y) = 0;
    
    
     virtual ~subscribe(){}
    
    
};

#endif	/* SUBSCRIBE_H */

