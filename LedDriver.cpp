/*
 * LedDriver.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: emrullah
 */

#include "LedDriver.h"

//LedDriver::LedDriver(GPIO_TypeDef* port)
//    : GPIODevice(port){}
LedDriver::LedDriver(GPIO_TypeDef* port, uint16_t pin)
    : GPIODevice(port)
{
  configurePin(pin, Mode::Output, OutputType::PushPull, Speed::High, Pull::NoPull); // Configure pin for LED output
//    init();
}

//void LedDriver::init()
//{
//    enableClock();  // Enable the clock for the GPIO port
//    configure(Mode::Output, OutputType::PushPull, Speed::High, Pull::NoPull); // Configure pin for LED output
//}

void LedDriver::toggle()
{
  _port->ODR ^= (1 << currentPin);
}

void LedDriver::toggle(uint16_t pin)
{
  _port->ODR ^= (1 << pin);
}

void LedDriver::set(LedState state)
{
  if (state == LedState::ON)
  {
    _port->BSRR = (1 << currentPin); // Set pin
  }
  else
  {
    _port->BSRR = (1 << (currentPin + 16));  // Reset pin
  }
}

void LedDriver::set(uint16_t pin, LedState state)
{
  if (state == LedState::ON)
  {
    _port->BSRR = (1 << pin); // Set pin
  }
  else
  {
    _port->BSRR = (1 << (pin + 16));  // Reset pin
  }
}
