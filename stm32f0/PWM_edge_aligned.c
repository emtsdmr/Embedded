#include "stm32f0xx.h"
#include "LCDfunctions.h"
#include "ADC.h"

int main(void) 
{	
    ADCinitialise();
	ADCchannelSelect(1);

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODER11_0); // Alternate function mode: 10
    GPIOA->MODER |= GPIO_MODER_MODER11_1;
    
    GPIOA->AFR[1] = 0b10000000000000; // Alternate function select: AF2 for TIM1_CH4 of PortAPin 11, 1 for high
    
    TIM1->PSC = 1000; // setting prescaler
    TIM1->ARR = 500;  // Auto-reload-preload enable, Period
    TIM1->CCR4 = 500; // Capture-compare register , DutyCycle
    TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 ; // Output compare mode, 110: PWM mode 1: channel 4 is active
    TIM1->CCMR2 |=  TIM_CCMR2_OC4PE; // Preload register on TIM1_CCR4 enabled.TIM1_CCR4 can't be written at anytime
                                                                                        // TIM1_CCR4 preload value is loaded in the active register at each update event.
    TIM1->CCER |= TIM_CCER_CC4E; // 1: On - OC1 signal is output on the corresponding output pin depending on MOE
    TIM1->BDTR |= TIM_BDTR_MOE; // Main output enable: 1: OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in TIMx_CCER register).
    TIM1->CR1 |= TIM_CR1_CEN; // Counter enable
    TIM1->EGR |= TIM_EGR_UG;  // initialising all registers before starting the counter
    
    while(1)
    {
        LCDsendInt(ADC1->DR); //the conversion result from the last converted channel
        delay();
    }
}
