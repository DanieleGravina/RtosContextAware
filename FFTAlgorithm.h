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

class FFTAlgorithm : public SignalProcessing{
public:
    
    /**
     * Get the N data from ADC and process the data with the choosen algorithm implementation
     * @param Data
     * @param N
     * @return true if the algorithm has detect an indoor environment, otherwise return false.
     */
     bool ProcessData(double *const Data, const unsigned short N);
     
private:
    
    CFFT fft;
    
    complex *f;
    
};



#endif	/* FFTALGORITHM_H */
