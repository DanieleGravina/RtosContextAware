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

/**
 * Enum to set if it get sample with timer or not
 */
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

/**
 * LightAware is class that given an FFT algorithm, take data from ADC 
 * and send it to the algorithm. 
 * 
 * @param algorithm
 * @param adc_init
 */
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
    double lightLevel();
    
protected:
    
    /**
     * Thread that push adc value to the queue
     * @return 
     */
    void *pushADCValue();
    
    /**
     * Thread that reads adc samples from queue
     * and send it to the algorithm
     * @return 
     */
    void *popToFFT();
   
    /**
     * Thread that push adc value to the queue
     * with the timer library
     * @return 
     */
    void *pushADCValueWithTimer();
    
    /**
     * Helper to allow pthread for pushADCValue
     * @param context
     * @return 
     */
    static void *pushADCValueHelper(void *context)
    {
        return ((light_aware *)context)->pushADCValue();
    }
    
    /**
     * Helper to allow pthread for pushADCValueWithTimer
     * @param context
     * @return 
     */
    static void *pushADCValueWithTimerHelper(void *context){
        return ((light_aware *)context)->pushADCValueWithTimer();
    }
    
    /**
     * Helper to allow pthread for popToFFT
     * @param context
     * @return 
     */
    static void *popToFFTHelper(void *context)
    {
        return ((light_aware *)context)->popToFFT();
    }
    
    /**
     * set the value that says if we are inside or outside 
     * @param value
     */
    void setIsOutside(bool value);
    
    /**
     * get the value that says if we are inside or outside
     * @param value
     */
    void getIsOutside(bool *value);
    
private:
    
    /**
     * Initialize ADC 
     * @param type
     */
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

