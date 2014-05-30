#include <FFTAlgorithm.h>

bool FFTAlgorithm::ProcessData(double *const Data, const unsigned short N){
    complex *f = new complex[N];
    
    bool result;
    
    for (int i = 0; i < N; ++i){
        f[i] = Data[i];
    }
    
    fft.Forward(f, N);
    
    if(f[INDEX].norm() > 80000 && \
                     f[INDEX].norm() > fft.Avg(f, N))
        result = true;
    else
        result = false;
    
    delete[] f;
    
    return result;
    
}

unsigned int FFTAlgorithm::getNumOfSamples(){
    return SAMPLES;
}
    
unsigned int FFTAlgorithm::getSampleFrequency(){
    return FREQUENCY;
}
