#include "test.h"

void foo(){
    printf("in->out");
}

void foo2(){
    printf("out->in");
}

int test()
{
    /*first choose the desired algorithm for signal processing*/
    FFTAlgorithm algorithm;
    
    /*second choose the subscription implementation for the context aware */
    subscribe_light_aware sub;
    
    /*call the desired context aware implementation*/
    light_aware light_awareness(algorithm, ADCInit::NO_TIMER, sub);
    
    /*register callback function with a trigger rule*/
    light_awareness.registration(TRIGGER_rule::IN_OUT, &foo);
    light_awareness.registration(TRIGGER_rule::OUT_IN, &foo2);
    
}

