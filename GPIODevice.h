/*
 * GPIODevice.h
 *
 *  Created on: Oct 16, 2024
 *      Author: emrullah
 */

#ifndef SRC_GPIODEVICE_H_
#define SRC_GPIODEVICE_H_

class GPIODevice {
public:
  enum class Mode { Output, Input }; // TODO: Add alternate function mode, analog mode
  enum class OutputType { PushPull, OpenDrain };
  enum class Speed { Low, Medium, High };
  enum class Pull { NoPull, PullUp, PullDown };

  GPIODevice(GPIO_TypeDef* _port);  // Constructor to initialize the GPIO port and pin
  virtual ~GPIODevice() = default;          // Virtual destructor for proper cleanup
  void configurePin(uint16_t pin, Mode mode, OutputType outputType, Speed speed, Pull pull); // Generalized configuration

//  virtual void init() = 0;                  // Pure virtual function for initializing the device

protected:
  GPIO_TypeDef* port;
  //uint32_t port;                           // GPIO Port (e.g., GPIOA, GPIOB)

  void enableClock();                       // Method to enable clock for the GPIO port

private:
  uint16_t currentPin;
  void setMode(Mode mode);                  // Configure GPIO mode (input/output)
  void setOutputType(OutputType outputType); // Configure output type (push-pull, open-drain)
  void setSpeed(Speed speed);               // Configure GPIO speed (low, medium, high)
  void setPull(Pull pull);                  // Configure pull-up/pull-down resistors
//public:
//	GPIODevice();
//	virtual ~GPIODevice();
//	GPIODevice(const GPIODevice &other);
//	GPIODevice(GPIODevice &&other);
//	GPIODevice& operator=(const GPIODevice &other);
//	GPIODevice& operator=(GPIODevice &&other);
};

#endif /* SRC_GPIODEVICE_H_ */
