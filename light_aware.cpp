#include <light_aware.h>

light_aware::light_aware(SignalProcessing &algorithm, ADCInit::ADCInit_ adc_init, subscribe& sub):
        adc(1), _algorithm(algorithm), SAMPLES(algorithm.getNumOfSamples()),
        frequency(algorithm.getSampleFrequency()),
        isOutside(false), mutexQueue(PTHREAD_MUTEX_INITIALIZER),
        mutexIsOutside(PTHREAD_MUTEX_INITIALIZER), cond(PTHREAD_COND_INITIALIZER),
        firstTime(true), avg(0), ContextAware(sub)
{ 
    
    a_samples = new double[SAMPLES];
    initADC(adc_init);
}

light_aware::~light_aware(){
    
    delete[] a_samples;
    
}

void light_aware::initADC(ADCInit::ADCInit_ type){
    
    //initialize adc
    adcIn::mode(Mode::INPUT_ANALOG); //configurazione ingresso analog
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //clock gating
    
    adc.scanConvMode(DISABLE);
    adc.continuousConvMode(DISABLE);
    adc.externalTrigConv(ExternalTrigConv::T1_CC1);
    adc.resolution(Resolution::RES_12);
    adc.dataAlign(DataAlign::Right);
    adc.nbrOfConversion(1);
    
    if(type == ADCInit::NO_TIMER){
       adc.externalTrigConvEdge(ExternalConvEdge::None); 
    }
    else{
        adc.externalTrigConvEdge(ExternalConvEdge::Rising);
    }
    
    adc.init();
    adc.regularChannelConfig(Channel::Channel_8, 1, SampleTime::Cycles3);
    
    if(type == ADCInit::NO_TIMER){
        pthread_create( &producer, NULL, &light_aware::pushADCValueHelper, this);
    }
    else
    {
       pthread_create( &producer, NULL, &light_aware::pushADCValueWithTimerHelper, this); 
    }
    
    pthread_create( &consumer, NULL, &light_aware::popToFFTHelper, this);
}

void *light_aware::popToFFT(void){
    
    unsigned int samples = 0;
    double acc = 0;
    
    for(;;){
        
         pthread_mutex_lock(&mutexQueue);
         
         while(Queue.empty()) pthread_cond_wait(&cond, &mutexQueue);
         
         a_samples[samples] = Queue.front();
         Queue.pop();
         
         pthread_mutex_unlock(&mutexQueue);
         
         acc += a_samples[samples];
         
         samples++;
    
         if(samples == SAMPLES){
             
             if(_algorithm.ProcessData(a_samples, SAMPLES))
                 setIsOutside(false);
             else
                 setIsOutside(true);
      
             avg = acc/(double)SAMPLES;    
             
             acc = 0;
             samples = 0;
         }
    }
    
    return 0;
}

void *light_aware::pushADCValue(void){
    
    double temp;
    
    for(;;){
        
        adc.softwareStartConv();
        while(adc.getFlagStatus(ADC_FLAG_EOC) == RESET){}
        
        temp = adc.getConversionValue();
        
        pthread_mutex_lock(&mutexQueue);
        
        Queue.push(temp);
        
        pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&mutexQueue);
        
        usleep(25*100);
    }
    
    return 0;
}

void *light_aware::pushADCValueWithTimer(){
    //TODO not implemented
    printf("Error: push adc value with timer library not implemented\n");
    pushADCValue();
    
    return 0;
}

void light_aware::setIsOutside(bool value){
    
    pthread_mutex_lock(&mutexIsOutside);
    isOutside = value;
    pthread_mutex_unlock(&mutexIsOutside);
    
    if(firstTime){
        prec = value;
        firstTime = false;
    }
    
    if(prec != value){
        _sub.change(value);
        prec = value;
    }
}

void light_aware::getIsOutside(bool *value){
    
    pthread_mutex_lock(&mutexIsOutside);
    *value = isOutside;
    pthread_mutex_unlock(&mutexIsOutside);
}

bool light_aware::isOutdoor(){
    
    bool temp;
    
    pthread_mutex_lock(&mutexIsOutside);
    temp = isOutside;
    pthread_mutex_unlock(&mutexIsOutside);
    
    return temp;
}

double light_aware::getMeasure(){
    return avg;
}
