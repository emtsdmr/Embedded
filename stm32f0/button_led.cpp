#include "stm32f0xx.h"

// Delay function
void wait(int time)
{
    int j;
    for (int i = 0; i < time; i++)
        j++;
}

int main(void) 
{

    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; // 0x00080000   19th bit 
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;    

    GPIOC -> MODER |= GPIO_MODER_MODER6_0;
    GPIOC -> MODER &= ~(GPIO_MODER_MODER6_1);
    //OTYPER  0: Output push-pull(reset state)  1: Output open-drain
    GPIOC -> OTYPER &= ~(GPIO_OTYPER_OT_6); // and ~0100 0000 makes 6th pin 0
    //Ospeedr
    GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6; //0x00003000  11:high speed
    //PUPDR
    GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);
    
    GPIOB -> MODER &= ~(GPIO_MODER_MODER1);
    GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR1);
    
    volatile char btnPressed=0;
    volatile int pressedConfidence=0;
    volatile int releasedConfidence=0;   
    volatile int threshold=150;
    volatile char LEDstate;
    
    while(1)
    {
        if (GPIO -> IDR & GPIO_IDR_1)
        {
            if (btnPressed == 0)
            {
                if (pressedConfidence > threshold)
                {
                    if(LEDstate == 0)
                    {
                        LEDstate=1;
                        GPIOC ->BSRR |= GPIO_BSRR_BS_6; 
                    }
                    else
                    {
                        LEDstate=0;
                        GPIOC ->BSRR |= GPIO_BSRR_BR_6; 
                    }
                    btnPressed=1;
                }
                else
                {
                    pressedConfidence ++;
                    releasedConfidence = 0;
                }
            }
        }
        
        else
        {
            if (btnPressed == 1)
            {
                if (releasedConfidence > threshold)
                {
                    btnPressed=0;
                }
                else
                {
                    pressedConfidence = 0;
                    releasedConfidence ++;
                }
            }
        }
 
    }
}