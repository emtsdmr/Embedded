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

void ButtonDriver::enableInterrupt(uint16_t pin, uint32_t priority = 1)
{
  // Enable SYSCFG clock
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  // Use port-specific constants for EXTI configuration
  if (pin <= 15) {
    uint8_t portCode;
    if (port == GPIOA) portCode = GPIODevice::GPIOA_EXTI;
    else if (port == GPIOB) portCode = GPIODevice::GPIOB_EXTI;
    else if (port == GPIOC) portCode = GPIODevice::GPIOC_EXTI;
    else if (port == GPIOD) portCode = GPIODevice::GPIOD_EXTI;
    else if (port == GPIOE) portCode = GPIODevice::GPIOE_EXTI;
    else return;  // Handle unsupported port

    SYSCFG->EXTICR[pin / 4] |= (portCode << (4 * (pin % 4)));

    // Enable interrupt mask for the pin and configure trigger
    EXTI->IMR |= (1UL << pin);
    EXTI->FTSR |= (1UL << pin);  // Falling edge trigger

    // Set priority and enable NVIC interrupt based on pin range
    if (pin >= 5 && pin <= 9) {
      NVIC_SetPriority(EXTI9_5_IRQn, priority);
      NVIC_EnableIRQ(EXTI9_5_IRQn);
    }
    else if (pin >= 10 && pin <= 15) {
      NVIC_SetPriority(EXTI15_10_IRQn, priority);
      NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
    else if (pin <= 4) {
      NVIC_SetPriority((IRQn_Type)(EXTI0_IRQn + pin), priority);
      NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn + pin));
    }
  }
}

//extern "C" void EXTI15_10_IRQHandler(void)
//{
//    if ((EXTI->PR & EXTI_PR_PR13) != 0) {
//        EXTI->PR = EXTI_PR_PR13;    // Clear interrupt pending bit for pin 13
//        led.toggle();                                // Toggle the LED
//    }
//    // Add conditions here for other pins as needed
//}

