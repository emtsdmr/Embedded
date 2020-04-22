#include "stm32f0xx.h"

int main(void) 
{

    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;    

    GPIOC -> MODER = 0b00000000000001010101000000000000; // 0x00055000
    GPIOC -> OTYPER = 0;
    GPIOC ->OSPEEDR = 0b00000000000011111111000000000000; //0x000FF000 
    GPIOC ->PUPDR = 0;
    
    GPIOB -> MODER = 0b01010101000000000000000000000000; // 0x55000000
    GPIOC -> OTYPER = 0;
    GPIOC ->OSPEEDR = 0b11111111000000000000000000000000; // 0xFF000000
    GPIOB -> PUPDR = 0;
    
    char character = "A"; //0b01000001
    
    if (character & 0b00000001)
        GPIOB ->BSRR |= GPIO_BSRR_BS_12;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_12;
        
    if (character & 0b00000010)
        GPIOB ->BSRR |= GPIO_BSRR_BS_13;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_13;
        
    if (character & 0b00000100)
        GPIOB ->BSRR |= GPIO_BSRR_BS_14;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_14;
        
    if (character & 0b00001000)
        GPIOB ->BSRR |= GPIO_BSRR_BS_15;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_15;
        
    if (character & 0b00010000)
        GPIOB ->BSRR |= GPIO_BSRR_BS_6;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_6;
    
    if (character & 0b00100000)
        GPIOB ->BSRR |= GPIO_BSRR_BS_7;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_7;
        
    if (character & 0b01000000)
        GPIOB ->BSRR |= GPIO_BSRR_BS_8;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_8;
        
    if (character & 0b10000000)
        GPIOB ->BSRR |= GPIO_BSRR_BS_9;
    else
        GPIOB ->BSRR |= GPIO_BSRR_BR_9;
    
    while(1)
    {

    }
}
