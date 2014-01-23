/* 
 * File:   adc.h
 * Author: daniele
 *
 * Created on 23 dicembre 2013, 18.07
 */

#ifndef ADC_H
#define	ADC_H

#include "miosix.h"
#include "interfaces/arch_registers.h"
#include <stdint.h>
#include <cstdio>

#define uint8_t unsigned char
#define uint16_t unsigned short


#define  RCC_APB2RSTR_ADC1RST                ((uint32_t)0x00000200)

#define ADC_Resolution_shift                       6
#define ADC_ExternalTrigConvEdge_shift             7
#define ADC_Align_shift                            2
#define ADC_Trigger_shift                          6

/////////////////////////////////////////////////
/// defgroup ADC Flag
/////////////////////////////////////////////////
#define ADC_FLAG_AWD                               ((uint8_t)0x01)
#define ADC_FLAG_EOC                               ((uint8_t)0x02)
#define ADC_FLAG_JEOC                              ((uint8_t)0x04)
#define ADC_FLAG_JSTRT                             ((uint8_t)0x08)
#define ADC_FLAG_STRT                              ((uint8_t)0x10)
#define ADC_FLAG_OVR                               ((uint8_t)0x20)   

class Resolution
{
public:
    /**
     * ADC Resolution( 12, 10 ,8, 6 bit)
     * \code ADCx::Resolution(Resolution::RES_12);\endcode
     */
    enum Resolution_
    {
        RES_12 = 0,
        RES_10 = 1,
        RES_8  = 2,
        RES_6  = 3
    };
private:
    Resolution(); //Just a wrapper class, disallow creating instances
};

class ExternalTrigConv
{
public:
    /**
     * ADC External Trigger Conversion (T1, T2, T4, T5, T8, External Interrupt)
     * \code ADCx::ExternalTrigConv(Trigger_::T1_CC1);\endcode
     */
    enum Trigger_
    {
        T1_CC1  =  0,
        T1_CC2  =  1,
        T1_CC3  =  2,
        T2_CC2  =  3,
        T2_CC3  =  4,
        T2_CC4  =  5,
        T2_TRGO =  6,
        T3_CC1  =  7,
        T3_TRGO =  8, 
        T4_CC4  =  9,
        T5_CC1  = 10,
        T5_CC2  = 11,
        T5_CC3  = 12,
        T8_CC1  = 13,
        T8_TRGO = 14,
        Ext_IT11 = 15
    };
private:
    ExternalTrigConv(); //Just a wrapper class, disallow creating instances
};

class ExternalConvEdge
{
public:
    /**
     * ADC External Conversion Edge( None, Rising, Falling, Rising and Falling)
     * \code ADCx::ExternalConvEdge(Edge_::Rising);\endcode
     */
    enum Edge_
    {
        None          = 0,
        Rising        = 1,
        Falling       = 2,
        RisingFalling = 3
    };
private:
    ExternalConvEdge(); //Just a wrapper class, disallow creating instances
};

class DataAlign
{
public:
    /**
     * ADC Data Alignment( Right, Left)
     * \code ADCx::DataAlign(Alignment_::Right);\endcode
     */
    enum Alignment_
    {
        Right = 0,
        Left  = 8
    };
private:
    DataAlign(); //Just a wrapper class, disallow creating instances
};

class Channel
{
public:
    /**
     * ADC Channel( 0, 1, 2, ..., 15)
     * \code ADCx::Channel(Channel_::Channel_0);\endcode
     */
    enum Channel_
    {
        Channel_0 = 0,
        Channel_1 = 1,
        Channel_2 = 2,
        Channel_3 = 3,
        Channel_4 = 4,
        Channel_5 = 5,
        Channel_6 = 6,
        Channel_7 = 7,
        Channel_8 = 8,
        Channel_9 = 9,
        Channel_10 = 10,
        Channel_11 = 11,
        Channel_12 = 12,
        Channel_13 = 13,
        Channel_14 = 14,
        Channel_15 = 15
    };
private:
    Channel(); //Just a wrapper class, disallow creating instances
};

class SampleTime
{
public:
    /**
     * ADC Sample Time(3, 15, 28, 56, 84, 112, 144, 480 cycles)
     * \code ADCx::SampleTime(SampleTime_::Cycles3);\endcode
     */
    enum SampleTime_
    {
        Cycles3   = 0,
        Cycles15  = 1,
        Cycles28  = 2,
        Cycles56  = 3,
        Cycles84  = 4,
        Cycles112 = 5,
        Cycles144 = 6,
        Cycles480 = 7
    };
private:
    SampleTime(); //Just a wrapper class, disallow creating instances
};

/**
 * Base class to implement non template-dependent functions
 */
class ADCBase{
protected:
    
    static void deInit(uint8_t ADCx);
    
    /**
     * Write the register CR1 of the ADCx
     * @param ADCx
     * @param res
     * @param scanConvMode
     */
    static void CR1Impl(ADC_TypeDef* ADCx, Resolution::Resolution_ res, FunctionalState scanConvMode);
    
    /**
     * Write the register CR2 of the ADCx
     * @param ADCx
     * @param continuousConvMode
     * @param trigger
     * @param edge
     * @param align
     */
    static void CR2Impl(ADC_TypeDef* ADCx, FunctionalState continuousConvMode, ExternalTrigConv::Trigger_ trigger, \
                        ExternalConvEdge::Edge_ edge, DataAlign::Alignment_ align);
    /**
     * Write the register SQR1 of the ADCx
     * @param ADCx
     * @param nbrOfConversion
     */
    static void SQR1Impl(ADC_TypeDef* ADCx, uint8_t nbrOfConversion);
    
    /**
     * Deinitialize the ADC registers
     */
    static void deInit();
    
    /**
     * SMPRs register channel configuration
     * @param adc
     * @param channel
     */
    static void SMPRConfig(ADC_TypeDef* ADCx, Channel::Channel_ channel, SampleTime::SampleTime_ sample);
    
    /**
     * SQRs register sample time configuration
     * @param adc
     * @param sample
     * @param rank
     */
    static void SQRConfig(ADC_TypeDef* ADCx, Channel::Channel_ channel, SampleTime::SampleTime_ sample, uint8_t rank);
    
    /**
     * Enable the adc peripheral
     * @param ADCx
     */
    static void enable(ADC_TypeDef* ADCx);
    
    /**
     * Disable the adc peripheral
     * @param ADCx
     */
    static void disable(ADC_TypeDef* ADCx);
    
    static ADC_TypeDef* getADC(uint8_t ADCx);
};

/**
 * class for ADC driver
 */
class Adc : private ADCBase{
    
public :
    
    Adc(uint8_t adc):initStatus(0){
        ADCx = getADC(adc);
    };
    
    ~Adc(){
        disable(ADCx);
    }
    
    /**
     * Configures the ADC resolution dual mode. 
     * @param res
     * initStatus = 1000000
     */
    void resolution(Resolution::Resolution_ res){
        //initStatus |= (uint8_t)64;
        initStatus++;
        _resolution = res;
    }
    
    /**
     * Specifies whether the conversion 
       is performed in Scan (multichannels) 
       or Single (one channel) mode.
     * @param scanConvMode
     */
    void scanConvMode(FunctionalState scanConversionMode){
        initStatus++;
        _scanConvMode = scanConversionMode;
    }
    
    /**
     * 
     * @param continuosConversionMode
     */
    void continuousConvMode(FunctionalState continuosConversionMode){
        initStatus++;
        _continuosConvMode = continuosConversionMode;
    }
    
    /**
     * 
     * @param externalConversionEdge
     */
    void externalTrigConvEdge(ExternalConvEdge::Edge_ externalConversionEdge){
        initStatus++;
        _externalConvEdge = externalConversionEdge;
    }
    
    /**
     * 
     * @param externalTrigger
     */
    void externalTrigConv(ExternalTrigConv::Trigger_ externalTrigger){
        initStatus++;
        _trigger = externalTrigger;
    }          
    
    /**
     * 
     * @param alignment
     */
    void dataAlign(DataAlign::Alignment_ alignment){
        initStatus++;
        _align = alignment;
    }
    
    /**
     * Specify the number of conversion : range 1 to 16
     * @param nbrOfConversion
     */
    void nbrOfConversion(uint8_t numberOfConversion){
        initStatus++;
        _nbrOfConversion = numberOfConversion;
    }
    
    /**
     * Initialize the ADC : all parameters must be set, otherwise will not do anything
     */
    void init(){
        
        if(initStatus == 7){
            
            iprintf("init\n");
            
            deInit();

            CR1Impl(ADCx, _resolution, _scanConvMode);
            CR2Impl(ADCx, _continuosConvMode, _trigger, _externalConvEdge, _align);
            SQR1Impl(ADCx, _nbrOfConversion);

            enable(ADCx);
        }
        
    }
    
    /**
     * Regular Channel Configuration
     * @param channel
     * @param Rank
     * @param sampleTime
     */
    void regularChannelConfig(Channel::Channel_ channel, uint8_t Rank, SampleTime::SampleTime_ sampleTime){
        SMPRConfig(ADCx, channel, sampleTime);
        SQRConfig(ADCx, channel, sampleTime, Rank);
    }
    
    /**
     * Enable the selected ADC software start conversion for the regular channel
     */
    void softwareStartConv(){
        ADCx->CR2 |= (uint32_t)ADC_CR2_SWSTART;
    }
    
    
    FlagStatus getFlagStatus(uint8_t ADC_FLAG)
    {
      FlagStatus bitstatus = RESET;

      /* Check the status of the specified ADC flag */
      if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
      {
        /* ADC_FLAG is set */
        bitstatus = SET;
      }
      else
      {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
      }
      /* Return the ADC_FLAG status */
      return  bitstatus;
    }
    
    /**
     * Get the converted value
     * @return 
     */
    uint16_t getConversionValue(){
        return (uint16_t) ADCx->DR;
    }

private :
    ADC_TypeDef* ADCx;
    Resolution::Resolution_ _resolution;
    FunctionalState _scanConvMode;
    FunctionalState _continuosConvMode;
    ExternalConvEdge::Edge_ _externalConvEdge;
    ExternalTrigConv::Trigger_ _trigger;
    DataAlign::Alignment_ _align;
    uint8_t _nbrOfConversion;
    
    //variable for init status control
    uint8_t initStatus;
};

#endif	/* ADC_H */

