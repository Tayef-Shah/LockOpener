#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpio_helper.h"
#include "../includes/constants.h"

const int STEPPER_PIN[4] = { 17, 22, 23, 24 };
const int STEPPER_SEQ[8][4] = { {1,0,0,1},
							 {1,0,0,0},
							 {1,1,0,0},
							 {0,1,0,0},
							 {0,1,1,0},
							 {0,0,1,0},
							 {0,0,1,1},
							 {0,0,0,1} };

void stepperInit(GPIO_Handle gpio) {
	//Set Stepper motor to output
	for (int i = 0; i < 4; ++i)
		setToOutput(gpio, STEPPER_PIN[i]);
}

//Step once (512 per rotation), in direction (1 for CW, -1 for CCW)
void stepStepperOnce(GPIO_Handle gpio, int direction) {
	//printf("Stepper Motor (%d) - Stepping Once\n", direction);
    for (int a = 0; a < 8; ++a) {
        for (int i = 0; i < 4; ++i) {
            int index = i;
            int pin = STEPPER_PIN[index];
            if (STEPPER_SEQ[direction == 1 ? a : 7 - a][index])
                outputOn(gpio, pin);
            else
                outputOff(gpio, pin);
        }
        usleep(2000);
    }
}

#endif