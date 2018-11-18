#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"
#include "constants.h"

#include <stdlib.h>
#include <unistd.h>

//Step once (512 per rotation), in direction (1 for CW, -1 for CCW)
void stepOnce(GPIO_Handle gpio, int direction) {
    int counter = 0;
    while (1) {
        for (int i = 0; i < 4; ++i) {
            int pin = stepperPin[i];
            if (stepperSeq[counter][pin] != 0)
                outputOn(gpio, pin);
            else
                outputOff(gpio, pin);
        }
        counter += direction;

        // Restart cycle
        if (counter >= stepperCount)
            counter = 0;
        if (counter < 0)
            counter = stepperCount + direction;
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
        usleep(750);
    }

    return 0;
}