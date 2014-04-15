/* 
 * File:   SignalProcessingAlgorithm.h
 * Author: daniele
 *
 * Created on 6 aprile 2014, 17.22
 */

#ifndef SIGNALPROCESSINGALGORITHM_H
#define	SIGNALPROCESSINGALGORITHM_H

#include <cstdio>

const int INDEX = 102;

class SignalProcessing{
public:
    /**
     * Get the N data from ADC and process the data with the choosen algorithm implementation
     * @param Data
     * @param N
     * @return true if the algorithm has detect an indoor environment, otherwise return false.
     */
    virtual bool ProcessData(double *const Data, const unsigned short N);
    
};

#endif	/* SIGNALPROCESSINGALGORITHM_H */

