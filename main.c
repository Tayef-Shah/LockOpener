#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"

#include "gpio/stepper_motor.h"

#include "constants.h"

int main() {

    //Initialize the GPIO pins
    GPIO_Handle gpio = initializeGPIO();

    //Set Stepper motor to output
    for (int i = 0; i < 4; ++i)
        setToOutput(gpio, stepperPin[i]);

    //Testing for stepper motor
    for (int i = 0; i < 512; ++i) {
        stepOnce(gpio, 1);
    }

    // Reset GPIO Pins
    for (int i = 0; i < 4; ++i)
        outputOff(gpio, stepperPin[i]);

    return 0;
}