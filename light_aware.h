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

using namespace std;
using namespace miosix;

typedef Gpio<GPIOB_BASE,0> adcIn;

const unsigned short SAMPLES = 512;

class light_aware {
public:
 
    light_aware();
    
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
    
    static void *pushADCValueHelper(void *context)
    {
        return ((light_aware *)context)->pushADCValue();
    }
    
    static void *popToFFTHelper(void *context)
    {
        return ((light_aware *)context)->popToFFT();
    }
    
    void setIsOutside(bool value);
    
    void getIsOutside(bool *value);
    
private:
    
    Adc adc;
    
    typedef Gpio<GPIOB_BASE,0> adcIn;
    
    pthread_t consumer, producer;
    
    SignalProcessing algorithm;
    
    queue<double> Queue;
    
    bool isOutside;
    
    pthread_mutex_t mutexQueue;
    
    pthread_mutex_t mutexIsOutside;
    
    pthread_cond_t cond; 
        
};



#endif	/* LIGHT_AWARE_H */

