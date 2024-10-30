/*
 * GPIODevice.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: emrullah
 */

#include "GPIODevice.h"
//#include <stdexcept>
#include "stm32f4xx_hal.h"

GPIODevice::GPIODevice(GPIO_TypeDef* _port)
{
  // TODO: Write isValid function to validate that the port is valid
  //if (_port != GPIOA && _port != GPIOB && _port != GPIOC && _port != GPIOD && _port != GPIOE) {
  //  throw std::invalid_argument("Invalid GPIO port!");
  //}
  port = _port;  // Assign if valid
  enableClock();
}

GPIODevice::GPIODevice(GPIO_TypeDef* _port, uint16_t pin)
{
  //if (_port != GPIOA && _port != GPIOB && _port != GPIOC && _port != GPIOD && _port != GPIOE) {
  //  throw std::invalid_argument("Invalid GPIO port!");
  //}
  port = _port;  // Assign if valid
  enableClock();
  currentPin = pin;
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
  else if (port == GPIOD)
  {
      __HAL_RCC_GPIOD_CLK_ENABLE();
  }
  else if (port == GPIOE)
  {
      __HAL_RCC_GPIOE_CLK_ENABLE();
  }
  //TODO: add an acceptable exception
  //else {
  //    // Handle invalid port or throw an exception
  //  throw std::invalid_argument("Invalid GPIO port!");
  //}

}

void GPIODevice::configurePin(uint16_t pin, Mode mode, OutputType outputType, Speed speed, Pull pull)
{
  currentPin = pin;
  if (mode != Mode::Unchanged) setMode(mode);
  if (outputType != OutputType::Unchanged) setOutputType(outputType);
  if (speed != Speed::Unchanged) setSpeed(speed);
  if (pull != Pull::Unchanged) setPull(pull);
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

