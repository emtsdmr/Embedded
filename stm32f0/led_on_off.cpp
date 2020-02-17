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
    //Enable the GPIO Clock for Port C using the AHB and RCC
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; // 0x00080000   19th bit 
    //Set any Control Registers for PortC Pin 6 for output mode(01)
    //Moder
    GPIOC -> MODER |= GPIO_MODER_MODER6_0;  // 0x00001000
    //OTYPER  0: Output push-pull(reset state)  1: Output open-drain
    GPIOC -> OTYPER &= ~(GPIO_OTYPER_OT_6); // and ~0100 0000 makes 6th pin 0
    //Ospeedr
    GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6; //0x00003000  11:high speed
    //PUPDR
    GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);
    
    while(1)
    {
        //Turn on the LED
        //BSRR
        GPIOC ->BSRR |= GPIO_BSRR_BS_6;
        //Wait
        wait(250000);
        //Turn off the LED
        //BRR
        GPIO -> BRR |= GPIO_BRR_BR_6;
        //Wait
        wait(250000);        
    }
}