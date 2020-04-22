#include "stm32f0xx.h"

#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))

int main(void) 
{
    // ADC Calibration

    ADC1 ->CR &= ~ADC_CR_ADEN; // disabling the AD enable
    ADC1 ->CR |= ADC_CR_ADCAL; //İnvoking the calibration
    
    while(( ADC1 ->CR & ADC_CR_ADCAL) != 0 )
    {
        //pass after reseting calibration
    }
    
    //Select a clock source for ADC
    
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // enabling peripheral bus for the adc
    RCC->CR2 |= RCC_CR2_HSI14ON; // enable the clock oscilator
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) //waiting until it is ready
    {
    }
    
    ADC1 ->CFGR2 |= ADC_CFGR2_CKMODE; // connecting  clock with the ADC using configuration register
    
    // Enable ADC
    ADC-> CCR |= ADC_CCR_TSEN; // ready to start temperature sensor
    ADC1 ->CR |= ADC_CR_ADEN; // enabling ADC
    
    while((ADC1->ISR & ADC_ISR_ADRDY) == 0)// wait until ADC enabled using the ADRDY bit of Interrupt status register
    {
    }
    
    ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; // sampling time selection
                                                                                                                                                                               // 111: 239.5 ADC clock cycles
    ADC1-> CHSELR |= ADC_CHSELR_CHSEL16; // selecting the 16. channel(temperature)
    ADC-> CCR |= ADC_CCR_VREFEN; // enabling voltage referance
     
     float slope=((float)(110-30))/((float)(*TEMP30_CAL_ADDR - *TEMP110_CAL_ADDR));
     
    while(1)
    {
        // start conversion
        
        ADC1-> CR | = ADC_CR_ADSTART; 
        
       while((ADC1->ISR & ADC_ISR_EOC) == 0) // checking if the conversion completed(end of conversion flag )
       {
        }
        float temperature = (slope * (*TEMP30_CAL_ADDR - ADC1-> DR)) + 30;
	LCDsendFloat(temperature);
   }
}
