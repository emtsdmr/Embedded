#include "stm32f0xx.h"
#include "functions.h"
#include  <stdio.h>

void setupDisplay()
{
     LCDSendInstruction(0b00111000); // Set to 8bit mode and 2 line display
     LCDSendInstruction(0b00001110); // turn on display
     LCDSendInstruction(0b00000110); //set the mode to increment address by one
     LCDSendInstruction(0b00000001); // clear display
}

int main(void) 
{

    initialisePorts();
/*  send characters****    
    setupDisplay();
     LCDSendCharacter('E');
     LCDSendCharacter('M');
     LCDSendInstruction(0b11000000); // go to the next line
     LCDSendCharacter('R');
     LCDSendCharacter('U');
     LCDSendCharacter('L');
*/    
    setupDisplay();
    char strNumber[6];
    unsigned int i=1994;
    sprintf(strNumber,"%d",i);
    LCDSendString(strNumber);
    
    
    while(1)
    {
        
    }
}