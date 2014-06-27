#include "test.h"

void foo(){
    printf("in-out");
}

void foo2(){
    printf("out-in");
}


int test()
{
    FFTAlgorithm algorithm;
    subscribe_light_aware sub;
    
    light_aware light_awareness(algorithm, ADCInit::NO_TIMER, sub);
    
    light_awareness.registration(TRIGGER_rule::IN_OUT, &foo);
    light_awareness.registration(TRIGGER_rule::OUT_IN, &foo2);
    
    light_awareness.unregistration(&foo2);
    
    led1::mode(Mode::OUTPUT);
    led2::mode(Mode::OUTPUT);
    
    
    for(;;){
        
        printf("light level: %g\n", light_awareness.getMeasure());
        
        if(light_awareness.isOutdoor()){
            printf("outside\n");
            led1::low();
            led2::high();
        }
        else
        {
            printf("inside\n");
            led1::high();
            led2::low();
        }
        
        usleep(25*100*512);
     
    }
           
    
}

