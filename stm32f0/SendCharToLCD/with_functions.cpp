#include "stm32f0xx.h"

#define LCDd0Pin 12
#define LCDd0Port GPIOB
#define LCDd1Pin 13
#define LCDd1Port GPIOB
#define LCDd2Pin 14
#define LCDd2Port GPIOB
#define LCDd3Pin 15
#define LCDd3Port GPIOB
#define LCDd4Pin 6
#define LCDd4Port GPIOC
#define LCDd5Pin 7
#define LCDd5Port GPIOC
#define LCDd6Pin 8
#define LCDd6Port GPIOC
#define LCDd7Pin 9
#define LCDd7Port GPIOC

void SetPortPin(GPIO_TypeDef *port, int pin)
{
    if (port == GPIOA)
    {
        RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
    }
    if (port == GPIOB)
    {
        RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;        
    }
    if (port == GPIOC)
    {
        RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    }
    if (port == GPIOF)
    {
        RCC -> AHBENR |= RCC_AHBENR_GPIODEN;
    }
    if (port == GPIO)
    {
        RCC -> AHBENR |= RCC_AHBENR_GPIOFEN;
    }
    
    port-> MODER &= ~(1 << ((pin*2)+1));
    port-> MODER |= ~(1 << (pin*2)); 
    
    port-> OTYPER &= ~(1 << pin);
    port -> OSPEEDR |= (1 << ((pin*2)+1)) | (1 << (pin*2));
    port -> PUPDR &= ~(1<< pin);
}

void initialisePorts()
{
    SetPortPin(LCDd0Port, LCDd0Pin);
    SetPortPin(LCDd1Port, LCDd1Pin);
    SetPortPin(LCDd2Port, LCDd2Pin);
    SetPortPin(LCDd3Port, LCDd3Pin);
    SetPortPin(LCDd4Port, LCDd4Pin);
    SetPortPin(LCDd5Port, LCDd5Pin);
    SetPortPin(LCDd6Port, LCDd6Pin);
    SetPortPin(LCDd7Port, LCDd7Pin);
}

void SendBitToPort(GPIO_TypeDef *port, int pinNumber, uint8_t bitState)
{
	if (bitState)
		port->BSRR |= (1 << pinNumber);
	else
		port->BRR |= (1 << pinNumber);
}

void SendCharToLCD(char character)
{
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000001);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000010);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000100);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00001000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00010000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00100000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b01000000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b10000000);
}

int main(void) 
{
/*
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
*/
    initialisePorts();
    SendCharToLCD('A');
    while(1)
    {
    }
}
