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
#include <fft.h>
#include <complex.h>
#include <adc.h>
#include <cstdio>
#include <inttypes.h>


//#define uint8_t unsigned char
//#define uint16_t unsigned short

using namespace std;
using namespace miosix;

const uint16_t SAMPLES = 512;

class light_aware {
public:
 
    light_aware();
    
    //virtual ~light_aware();
    
    bool isOutdoor();
    
    uint16_t lightLevel();
    
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
    
    CFFT fft;
    
    queue<complex> Queue;
    
    bool isOutside;
    
    pthread_mutex_t mutexQueue;
    
    pthread_mutex_t mutexIsOutside;
    
    pthread_cond_t cond; 
        
};



#endif	/* LIGHT_AWARE_H */

