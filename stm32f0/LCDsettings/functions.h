#ifndef LCDfunctions

#define LCDfunctions

#define LCDd0Pin 15
#define LCDd0Port GPIOB
#define LCDd1Pin 6
#define LCDd1Port GPIOC
#define LCDd2Pin 7
#define LCDd2Port GPIOC
#define LCDd3Pin 8
#define LCDd3Port GPIOC
#define LCDd4Pin 9
#define LCDd4Port GPIOC
#define LCDd5Pin 8
#define LCDd5Port GPIOA
#define LCDd6Pin 9
#define LCDd6Port GPIOA
#define LCDd7Pin 10
#define LCDd7Port GPIOA
#define EnablePin 14
#define EnablePort GPIOB
#define ReadWritePin 13
#define ReadWritePort GPIOB
#define RegisterSelectPin 12
#define RegisterSelectPort GPIOB

void delay(int time)
{
	volatile int i;
	for (i=0;i<time;i++)
	{
		
	}
}

void SetPortPin(GPIO_TypeDef *port, int pin)
{
    if (port == GPIOA)
        RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

    else if (port == GPIOB)
        RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;        
        
    else if (port == GPIOC)
        RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
        
    else if (port == GPIOD)
        RCC -> AHBENR |= RCC_AHBENR_GPIODEN;
        
    else if (port == GPIOF)
        RCC -> AHBENR |= RCC_AHBENR_GPIOFEN;
    
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

void LCDsetWrite()
{
    SendBitToPort(ReadWritePort, ReadWritePin, 0);
}

void LCDsetRead()
{
    SendBitToPort(ReadWritePort, ReadWritePin, 1);
}

void LCDcommandMode()
{
    SendBitToPort(RegisterSelectPort, RegisterSelectPin, 0);
}

void LCDcharacterMode()
{
    SendBitToPort(RegisterSelectPort, RegisterSelectPin, 1);
}

void LCDenable()
{
    delay(400); //time delay before enable > 40ns
    SendBitToPort(EnablePort, EnablePin, 1);
}

void LCDSendByte(char character)
{
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000001);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000010);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00000100);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00001000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00010000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b00100000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b01000000);
	SendBitToPort(LCDd0Port, LCDd0Pin, character & 0b10000000);
    delay(800); // time delay before disable >80ns
    SendBitToPort(EnablePort, EnablePin, 0); // disable port
}

void LCDSendCharacter(char character)
{
    LCDsetWrite();
    LCDcharacterMode();
    LCDenable();
    LCDSendByte(character);
}

void LCDSendInstruction(char character)
{
    LCDsetWrite();
    LCDcommandMode();
    LCDenable();
    LCDSendByte(character);
}

void LCDSendString(char *StringOfCharacter)
{
    while (*StringOfCharacter)
        LCDSendCharacter(*StringOfCharacter++);
}


#endif
