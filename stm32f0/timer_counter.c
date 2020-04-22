#include "stm32f0xx.h"
#include "LCDfunctions.h"

int main(void) 
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CR1 |= TIM_CR1_CEN | TIM_CR1_DIR | TIM_CR1_CMS_0; // Counter enable, direction(up and down counter), center alignmode(counts up and down)
    TIM1->PSC = 65535; // setting prescaler
    TIM1->ARR = 1000;  // Auto-reload-preload enable, counts max 1000
    
    while(1)
    {
        LCDsendInt(TIM1->CNT,5);
        delay();
    }
}