#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"
#include "constants.h"

//Step once (512 per rotation), in direction (1 for CW, -1 for CCW)
void stepOnce(GPIO_Handle gpio, int direction) {
    int counter = 0;
    for (int a = 0; a < 8; ++a) {
        for (int i = 0; i < 4; ++i) {
            int pin = stepperPin[i];
            if (stepperSeq[a][i])
                outputOn(gpio, pin);
            else
                outputOff(gpio, pin);
        }
        usleep(1000);
    }
}
int main() {

    //Initialize the GPIO pins
    GPIO_Handle gpio = initializeGPIO();

    //Set Stepper motor to output
    for (int i = 0; i < 4; ++i)
        setToOutput(gpio, stepperPin[i]);

    for (int i = 0; i < 512; ++i) {
        stepOnce(gpio, 1);
    }

    // Reset GPIO Pins
    for (int i = 0; i < 4; ++i)
        outputOff(gpio, stepperPin[i]);

    return 0;
}