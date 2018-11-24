#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpio_helper.h"
#include "../constants.h"

//Step once (512 per rotation), in direction (1 for CW, -1 for CCW)
void stepOnce(GPIO_Handle gpio, int direction) {
    for (int a = 0; a < 8; ++a) {
        for (int i = 0; i < 4; ++i) {
            int index = direction == 1 ? i : 7 - i;
            int pin = stepperPin[index];
            if (stepperSeq[a][index])
                outputOn(gpio, pin);
            else
                outputOff(gpio, pin);
        }
        usleep(1000);
    }
}

#endif