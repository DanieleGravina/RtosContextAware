/* 
 * File:   light_aware.h
 * Author: daniele
 *
 * Created on 3 gennaio 2014, 16.57
 */

#ifndef LIGHT_AWARE_H
#define	LIGHT_AWARE_H

#include <pthread.h>
#include <queue>
#include <miosix/_examples/context_aware/adc.h>
#include <cstdio>
#include <inttypes.h>
#include <SignalProcessingAlgorithm.h>
#include <FFTAlgorithm.h>

using namespace std;
using namespace miosix;

typedef Gpio<GPIOB_BASE,0> adcIn;

class ADCInit {
public:
    /**
     * ADCInit( TIMER or NOT_TIMER)
     */
    enum ADCInit_
    {
        NO_TIMER = 0,
        TIMER = 1
    };
private:
    ADCInit(); //Just a wrapper class, disallow creating instances
};

class light_aware {
public:
 
    light_aware(SignalProcessing &algorithm, ADCInit::ADCInit_ adc_init);
    
    ~light_aware();
    
    /**
     * Says if is an indoor or outdoor environment
     * @return true : outdoor, false : indoor
     */
    bool isOutdoor();
    
    /**
     * Says the current light intensity
     * @return light intensity
     */
    unsigned short lightLevel();
    
protected:
    
    void *pushADCValue();
    
    void *popToFFT();
    
    void *pushADCValueWithTimer();
    
    static void *pushADCValueHelper(void *context)
    {
        return ((light_aware *)context)->pushADCValue();
    }
    
    static void *pushADCValueWithTimerHelper(void *context){
        return ((light_aware *)context)->pushADCValueWithTimer();
    }
    
    static void *popToFFTHelper(void *context)
    {
        return ((light_aware *)context)->popToFFT();
    }
    
    
    void setIsOutside(bool value);
    
    void getIsOutside(bool *value);
    
private:
    
    void initADC(ADCInit::ADCInit_ type);
    
    Adc adc;
    
    typedef Gpio<GPIOB_BASE,0> adcIn;
    
    pthread_t consumer, producer;
    
    SignalProcessing& _algorithm;
    
    const unsigned int SAMPLES;
    const unsigned int frequency;
    
    queue<double> Queue;
    
    bool isOutside;
    
    pthread_mutex_t mutexQueue;
    
    pthread_mutex_t mutexIsOutside;
    
    pthread_cond_t cond; 
    
    double *a_samples;
    
    const light_aware& operator= ( const light_aware& other );
        
};



#endif	/* LIGHT_AWARE_H */

