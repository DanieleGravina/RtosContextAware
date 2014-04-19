

#include "miosix.h"
#include "light_aware.h"
#include <fft.h>
#include <goertzel_algorithm.h>
#include <complex.h>
#include <miosix/_examples/context_aware/adc.h>

using namespace std;
using namespace miosix;

typedef Gpio<GPIOD_BASE,14> led1;
typedef Gpio<GPIOD_BASE,15> led2;

typedef Gpio<GPIOB_BASE,0> adcIn;


int main()
{
    FFTAlgorithm algorithm;
    light_aware light_awareness(algorithm);
    
    led1::mode(Mode::OUTPUT);
    led2::mode(Mode::OUTPUT);
    
    for(;;){
        
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
    }
           
    
}
