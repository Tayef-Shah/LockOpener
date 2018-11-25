#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <stdio.h>

#include "../includes/constants.h"

const char* PIBLASTER_FILE = "/dev/pi-blaster";

const int SERVOPIN = 14;
const double SERVOMIN = 0.04;
const double SERVOMAX = 0.2;

// Turn the servo, in percentage from 0 to 1
void setPosition(FILE* file, double percentage) {
	if (percentage < 0 || percentage > 1)
		errorMessage(ERR_INCORRECT_PERCENTAGE);

	fprintf(file, "%d=%f\n", SERVOPIN, SERVOMIN + ((SERVOMAX - SERVOMIN) * percentage));
}

#endif