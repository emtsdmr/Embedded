/*
 * ButtonDriver.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: emrullah
 */

#include "ButtonDriver.h"

ButtonDriver::ButtonDriver(GPIO_TypeDef* port)
    : GPIODevice(port){}
ButtonDriver::ButtonDriver(GPIO_TypeDef* port, uint16_t pin)
    : GPIODevice(port, pin)
{
  configurePin(pin, Mode::Input, OutputType::PushPull, Speed::Low, Pull::NoPull);  // Configure pin for button input
//  init();
}

//void ButtonDriver::init()
//{
//  enableClock();  // Enable the clock for the GPIO port
//  configure(Mode::Input, OutputType::PushPull, Speed::Low, Pull::NoPull);  // Configure pin for button input
//}

ButtonDriver::ButtonState ButtonDriver::getState(uint16_t pin) const
{
  // Read the state of the button
  if ((GPIOC->IDR & (1 << pin)) != 0)
  {
      return ButtonState::OFF;
  }
  else
  {
      return ButtonState::ON;
  }
}

ButtonDriver::ButtonState ButtonDriver::getState() const
{
  // Read the state of the button
  if ((GPIOC->IDR & (1 << currentPin)) != 0)
  {
      return ButtonState::OFF;
  }
  else
  {
      return ButtonState::ON;
  }
}
