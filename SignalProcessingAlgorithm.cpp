#include <SignalProcessingAlgorithm.h>

bool SignalProcessing::ProcessData(double *const Data, const unsigned short N){
    complex *f = new complex[N];
    
    bool result;
    
    for (int i = 0; i < N; i++){
        f[i] = Data[i];
    }
    
    fft.Forward(f, N);
    
    /*for(int i = 1; i < N; i++){
            
            if(f[i].norm() > 80000 ){
                printf("maggiore del picco : %d\n", i);
                printf("val %f\n", f[i].norm());
            }
        }
    
    printf("media : %f\n", fft.Avg(f,N));*/
    
    if(f[INDEX].norm() > 80000 && \
                     f[INDEX].norm() > fft.Avg(f, N))
        result = true;
    else
        result = false;
    
    delete[] f;
    
    return result;
    
}
