

#include "miosix.h"
#include "light_aware.h"
#include <fft.h>
#include <goertzel_algorithm.h>
#include <complex.h>
#include <miosix/_examples/context_aware/adc.h>
#include "subscribe.h"

using namespace std;
using namespace miosix;

typedef Gpio<GPIOD_BASE,14> led1;
typedef Gpio<GPIOD_BASE,15> led2;

typedef Gpio<GPIOC_BASE,0> led3;

typedef Gpio<GPIOB_BASE,0> adcIn;


int main()
{
    FFTAlgorithm algorithm;
    subscribe sub;
    light_aware light_awareness(algorithm, ADCInit::NO_TIMER, sub);
    
    led1::mode(Mode::OUTPUT);
    led2::mode(Mode::OUTPUT);
    
    for(;;){
        
        printf("light level: %g\n", light_awareness.lightLevel());
        
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
