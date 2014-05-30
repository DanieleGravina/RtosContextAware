#include <goertzel_algorithm.h>

void GoertzelTransform::transform(double *const f, const unsigned short N){
    
    double d1 = 0.0;
    double d2 = 0.0;
    
    double y;
    
    for (unsigned short n = 0; n < N; ++n)
    {
        v[n] = f[n]*(0.54 - 0.46 * cos(2*M_PI*(double)n/N));
        
        if(v[n] > 0)
            _sum_abs += v[n];
        else 
            _sum_abs -= v[n];
        
        y  = v[n] + realW * d1 - d2;
        d2 = d1;
        d1 = y;
        
        
    }
    
    resultReal =  d1 - d2*realW*0.5;
    resultImaginary = imagW * d2;
    
}

bool GoertzelTransform::ProcessData(double *const Data, const unsigned short N){
    
     bool result = false;
        
        realW = 2.0 * cos(2.0 * M_PI * (double)k/N);
        imagW = sin(2.0 * M_PI * (double)k/N);
        
        v = new double[N];
        
        transform(Data, N);
        
        if(magnitude() > 80000 && magnitude() > _sum_abs)
            result = true;
        
        delete[] v;
        
        return result;
        
}

unsigned int GoertzelTransform::getNumOfSamples(){
    return SAMPLES;
}
    
unsigned int GoertzelTransform::getSampleFrequency(){
    return FREQUENCY;
}
