#include "adc.h"

using namespace miosix;


/** CR1 register Mask (SCAN and RES)*/
#define CR1_CLEAR_MASK            ((uint32_t)0xFCFFFEFF)

/** CR2 register Mask (ALIGN, EXTEN, EXTSEL, CONT)*/
#define CR2_CLEAR_MASK            ((uint32_t)0xC0FFF7FD)

/** ADC L Mask */
#define SQR1_L_RESET              ((uint32_t)0xFF0FFFFF) 

/** ADC SMPx mask */
#define SMPR1_SMP_SET             ((uint32_t)0x00000007)  
#define SMPR2_SMP_SET             ((uint32_t)0x00000007) 

/** ADC SQx mask */
#define SQR3_SQ_SET               ((uint32_t)0x0000001F)  
#define SQR2_SQ_SET               ((uint32_t)0x0000001F)  
#define SQR1_SQ_SET               ((uint32_t)0x0000001F) 

void ADCBase::CR1Impl(ADC_TypeDef* adc, Resolution::Resolution_ res, FunctionalState scanConvMode)
{
    uint32_t tmpreg1;
    
    //ADC_TypeDef* adc=reinterpret_cast<ADC_TypeDef*>(ADCx);

    ///////////////////////////////////////////
    // ADCx CR1 Configuration
    ///////////////////////////////////////////

    /** Get the ADCx CR1 value */
    tmpreg1 = adc->CR1;

    /** Clear RES and SCAN bits */
    tmpreg1 &= CR1_CLEAR_MASK;

    /** Configure ADCx: scan conversion mode and resolution
    * Set SCAN bit according to ADC_ScanConvMode value 
    * Set RES bit according to res value */ 

    tmpreg1 |= (uint32_t)(((uint32_t)scanConvMode << 8) | \
                                     res << ADC_Resolution_shift);
    /* Write to ADCx CR1 */
    adc->CR1 = tmpreg1;
}


void ADCBase::CR2Impl(ADC_TypeDef* adc, FunctionalState continuousConvMode, \
        ExternalTrigConv::Trigger_ trigger, ExternalConvEdge::Edge_ edge, DataAlign::Alignment_ align){
    
    uint32_t tmpreg1;
    
    ///////////////////////////////////////////
    // ADCx CR2 Configuration
    ///////////////////////////////////////////
    tmpreg1 = adc->CR2;

    /* Clear CONT, ALIGN, EXTEN and EXTSEL bits */
    tmpreg1 &= CR2_CLEAR_MASK;

    /** Configure ADCx: external trigger event and edge, data alignment and 
       continuous conversion mode 
       Set ALIGN bit according to ADC_DataAlign value 
       Set EXTEN bits according to ADC_ExternalTrigConvEdge value 
       Set EXTSEL bits according to ADC_ExternalTrigConv value 
       Set CONT bit according to ADC_ContinuousConvMode value */
    tmpreg1 |= (uint32_t)(align << ADC_Align_shift | \
                          trigger << ADC_Trigger_shift | 
                          edge << ADC_ExternalTrigConvEdge_shift | \
                          continuousConvMode << 1);

    /* Write to ADCx CR2 */
    adc->CR2 = tmpreg1;
    
    
}

void ADCBase::SQR1Impl(ADC_TypeDef* adc, uint8_t nbrOfConversion){
    
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;
    
  ///////////////////////////////////////////
  // ADCx SQR1 Configuration
  ///////////////////////////////////////////
  /* Get the ADCx SQR1 value */
  tmpreg1 = adc->SQR1;
  
  /* Clear L bits */
  tmpreg1 &= SQR1_L_RESET;
  
  /* Configure ADCx: regular channel sequence length */
  /* Set L bits according to ADC_NbrOfConversion value */
  tmpreg2 |= (uint8_t)(nbrOfConversion - (uint8_t)1);
  tmpreg1 |= ((uint32_t)tmpreg2 << 20);
  
  /* Write to ADCx SQR1 */
  adc->SQR1 = tmpreg1;
    
}

ADC_TypeDef* ADCBase::getADC(uint8_t ADCx){
    
    switch(ADCx){
        case 1 : return ADC1;
                 break;
        case 2:  return ADC2;
                 break;
        case 3:  return ADC3;
                 break;
        default: return ADC1;

    }
}

void ADCBase::deInit(){
    
    RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST;
}

void ADCBase::enable(ADC_TypeDef* ADCx){
    
    /** Set the ADON bit to wake up the ADC from power down mode */
    ADCx->CR2 |= (uint32_t)ADC_CR2_ADON;
}

void ADCBase::disable(ADC_TypeDef* ADCx){
    
    /** Set the ADON bit to power down the ADC */
    ADCx->CR2 &= (uint32_t)(~ADC_CR2_ADON);
}

void ADCBase::SMPRConfig(ADC_TypeDef* ADCx, Channel::Channel_ channel, SampleTime::SampleTime_ sample){
    
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  
  /** if ADC_Channel_10 ... ADC_Channel_18 is selected */
  if (channel > Channel::Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_SET << (3 * (channel - 10));
    
    /* Clear the old sample time */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)sample << (3 * (channel - 10));
    
    /* Set the new sample time */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_SET << (3 * channel);
    
    /* Clear the old sample time */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)sample << (3 * channel);
    
    /* Set the new sample time */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }
}

void ADCBase::SQRConfig(ADC_TypeDef* ADCx, Channel::Channel_ channel, SampleTime::SampleTime_ sample, uint8_t Rank){
    
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  
    /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_SET << (5 * (Rank - 1));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)channel << (5 * (Rank - 1));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_SET << (5 * (Rank - 7));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)channel << (5 * (Rank - 7));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_SET << (5 * (Rank - 13));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)channel << (5 * (Rank - 13));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
}



