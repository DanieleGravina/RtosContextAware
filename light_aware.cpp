#include <light_aware.h>

light_aware::light_aware():adc(1){ 
    
    isOutside = false;
    
    //initalize mutex
    mutexQueue = PTHREAD_MUTEX_INITIALIZER;
    mutexIsOutside = PTHREAD_MUTEX_INITIALIZER;
    cond = PTHREAD_COND_INITIALIZER;
    
    //initialize adc
    adcIn::mode(Mode::INPUT_ANALOG); //configurazione ingresso analog
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //clock gating
    
    adc.scanConvMode(DISABLE);
    adc.continuousConvMode(DISABLE);
    adc.externalTrigConv(ExternalTrigConv::T1_CC1);
    adc.externalTrigConvEdge(ExternalConvEdge::None);
    adc.resolution(Resolution::RES_12);
    adc.dataAlign(DataAlign::Right);
    adc.nbrOfConversion(1);
    
    adc.init();
    
    adc.regularChannelConfig(Channel::Channel_8, 1, SampleTime::Cycles3);
    
    pthread_create( &producer, NULL, &light_aware::pushADCValueHelper, NULL);
    pthread_create( &consumer, NULL, &light_aware::popToFFTHelper, NULL);
}

void *light_aware::popToFFT(void){
    
    uint16_t samples = 0;
    complex f[SAMPLES];
    
    for(;;){
        
         pthread_mutex_lock(&mutexQueue);
         
         while(Queue.empty()) pthread_cond_wait(&cond, &mutexQueue);
         
         f[samples] = Queue.front();
         Queue.pop();
         
         pthread_mutex_unlock(&mutexQueue);
         
         samples++;
    
         if(samples == SAMPLES){
             
             fft.Forward(f, SAMPLES);
             
             /*printf("real value: %f, imag value : %f, sum abs: %"PRIu32", magnitude: %"PRIu16"\n", \
                     fft.realValue(), fft.imagValue(), fft.sum_abs(), fft.magnitude());*/
             
             if(f[(uint16_t)SAMPLES/2].norm() > 10000 && \
                     f[(uint16_t)SAMPLES/2].norm() > fft.Avg(f, SAMPLES)){
                 setIsOutside(false);
             }
             else{
                 setIsOutside(true);
             }        
             
             samples = 0;
         }
    }
    
    return 0;
}

void *light_aware::pushADCValue(void){
    
    complex temp;
    
    for(;;){
        
        adc.softwareStartConv();
        while(adc.getFlagStatus(ADC_FLAG_EOC) == RESET){}
        
        temp = adc.getConversionValue();
        
        pthread_mutex_lock(&mutexQueue);
        
        Queue.push(temp);
        
        //printf("ADC value: %"PRIu16"\n", Queue.back());
        
        pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&mutexQueue);
        
        usleep(5*1000);
    }
    
    return 0;
}

void light_aware::setIsOutside(bool value){
    
    pthread_mutex_lock(&mutexIsOutside);
    isOutside = value;
    pthread_mutex_unlock(&mutexIsOutside);
}

void light_aware::getIsOutside(bool *value){
    
    pthread_mutex_lock(&mutexIsOutside);
    *value = isOutside;
    pthread_mutex_unlock(&mutexIsOutside);
}

bool light_aware::isOutdoor(){
    bool *result = NULL;
    
    getIsOutside(result);
    
    return *result;
}
