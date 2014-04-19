#include "SignalProcessingAlgorithm.h"
#include "FFTAlgorithm.h"

bool SignalProcessing::ProcessData(double *const Data, const unsigned short N){
    printf("Attention, you have to pass an implementation of this class, use of defualt");
    
    //Default implementation
    
    FFTAlgorithm algorithm;
    
    return algorithm.ProcessData(Data, N);
}