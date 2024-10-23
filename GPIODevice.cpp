/*
 * GPIODevice.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: emrullah
 */

#include "GPIODevice.h"

GPIODevice::GPIODevice(GPIO_TypeDef* _port)
{
  // Validate that the port is valid
  if (_port != GPIOA && _port != GPIOB && _port != GPIOC) {
    throw std::invalid_argument("Invalid GPIO port!");
  }
  port = _port;  // Assign if valid
  enableClock();
}

void GPIODevice::enableClock()
{
  // Enable the clock for the corresponding GPIO port
  if (port == GPIOA) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  else if (port == GPIOB) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  else if (port == GPIOC) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  else {
      // Handle invalid port or throw an exception
    throw std::invalid_argument("Invalid GPIO port!");
  }
  //TODO: Add others
}

void GPIODevice::configurePin(uint16_t pin, Mode mode, OutputType outputType, Speed speed, Pull pull)
{
  currentPin = pin;
  setMode(mode);
  setOutputType(outputType);
  setSpeed(speed);
  setPull(pull);
}

void GPIODevice::setMode(Mode mode)
{
  if (mode == Mode::Output)
  {
    port->MODER &= ~(1 << (currentPin * 2 + 1));
    port->MODER |= (1 << (currentPin * 2)); // Output mode
  }
  else if (mode == Mode::Input)
  {
    port->MODER &= ~(3UL << (currentPin * 2)); // Input mode
  }
  // TODO: Add similar checks for GPIOB and GPIOC and alternate function mode, analog mode
}

void GPIODevice::setOutputType(OutputType outputType)
{
  if (outputType == OutputType::PushPull)
  {
    port->OTYPER &= ~(1UL << currentPin); // Push-pull
  }
  else if (outputType == OutputType::OpenDrain)
  {
    port->OTYPER |= (1UL << currentPin);  // Open-drain
  }
  // Add similar checks for GPIOB and GPIOC
}

void GPIODevice::setSpeed(Speed speed)
{
  if (speed == Speed::Low)
  {
    port->OSPEEDR &= ~(3UL << (currentPin * 2)); // Low speed
  }
  else if (speed == Speed::Medium)
  {
     port->OSPEEDR &= ~(1UL << (currentPin * 2 + 1));
     port->OSPEEDR |= (1UL << (currentPin * 2)); // Medium speed
  }
  else if (speed == Speed::High)
  {
     port->OSPEEDR |= (3UL << (currentPin * 2)); // High speed
  }
  // Add similar checks for GPIOB and GPIOC
}

void GPIODevice::setPull(Pull pull)
{
  if (pull == Pull::NoPull)
  {
    port->PUPDR &= ~(3UL << (currentPin * 2)); // No pull-up, no pull-down
  }
  else if (pull == Pull::PullUp)
  {
    port->PUPDR &= ~(1UL << (currentPin * 2 + 1));
    port->PUPDR |= (1UL << (currentPin * 2)); // Pull-up
  }
  else if (pull == Pull::PullDown)
  {
    port->PUPDR |= (3UL << (currentPin * 2)); // Pull-down
  }
  // Add similar checks for GPIOB and GPIOC
}
//GPIODevice::GPIODevice() {
//	// TODO Auto-generated constructor stub
//
//}
//
//GPIODevice::~GPIODevice() {
//	// TODO Auto-generated destructor stub
//}
//
//GPIODevice::GPIODevice(const GPIODevice &other) {
//	// TODO Auto-generated constructor stub
//
//}
//
//GPIODevice::GPIODevice(GPIODevice &&other) {
//	// TODO Auto-generated constructor stub
//
//}
//
//GPIODevice& GPIODevice::operator=(const GPIODevice &other) {
//	// TODO Auto-generated method stub
//
//}
//
//GPIODevice& GPIODevice::operator=(GPIODevice &&other) {
//	// TODO Auto-generated method stub
//
//}

