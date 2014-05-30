/* 
 * File:   FFTAlgorithm.h
 * Author: daniele
 *
 * Created on 15 aprile 2014, 19.26
 */

#ifndef FFTALGORITHM_H
#define	FFTALGORITHM_H

#include <fft.h>
#include <complex.h>
#include <SignalProcessingAlgorithm.h>

const int INDEX = 102; 

/**
 * class that implement pure virtual SignalProcessing
 * using FFT algorithm
 */
class FFTAlgorithm : public SignalProcessing{
public:
    
    FFTAlgorithm(): SAMPLES(512), FREQUENCY(25*100){}
    
    bool ProcessData(double *const Data, const unsigned short N);

    unsigned int getNumOfSamples();

    unsigned int getSampleFrequency();
     
private:
    
    const unsigned int SAMPLES;
    const unsigned int FREQUENCY;
    
    CFFT fft;
    
    complex *f;
    
};



#endif	/* FFTALGORITHM_H */

