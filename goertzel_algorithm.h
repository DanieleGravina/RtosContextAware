/* 
 * File:   goertzel_algorithm.h
 * Author: daniele
 *
 * Created on 19 gennaio 2014, 19.55
 */

#ifndef GOERTZEL_ALGORITHM_H
#define	GOERTZEL_ALGORITHM_H

#include <cmath>
#include <SignalProcessingAlgorithm.h>

#define k 100 //frequency index

using namespace std;

/**
 * Fourier Transform with goertzel algorithm, with frequency k and number of samples N
 */
class GoertzelTransform : public SignalProcessing{
public :
    
    GoertzelTransform(): SAMPLES(512), FREQUENCY(25*100){} 
    
    bool ProcessData(double *const Data, const unsigned short N);
    
    unsigned int getNumOfSamples();

    unsigned int getSampleFrequency();
    
private:
    
    /**
     * Transform with the goertzel algorithm the vector f
     * @param f
     */
    void transform(double *const f, const unsigned short N);
    
    /**
     * Get the magnitude of the selected frequency
     * @return 
     */
    double magnitude() const{
        return sqrt(resultReal*resultReal + resultImaginary*resultImaginary);
    }
    
    
    double realW;
    double imagW;
    
    double _sum_abs;
    
    double resultReal, resultImaginary;
    
    double *v;
    
    const unsigned int SAMPLES;
    const unsigned int FREQUENCY;
};



#endif	/* GOERTZEL_ALGORITHM_H */

