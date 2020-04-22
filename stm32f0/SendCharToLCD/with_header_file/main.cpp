#include "stm32f0xx.h"
#include "functions.h"

int main(void) 
{

    initialisePorts();
    SendCharToLCD('A');
    while(1)
    {
    }
}
