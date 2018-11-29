#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <stdio.h>

#include "../includes/constants.h"

const char* PIBLASTER_FILE = "/dev/pi-blaster";

const int SERVOPIN = 14;
const double SERVOMIN = 0.04;
const double SERVOMAX = 0.2;

FILE* servoInit() {
	FILE* file = fopen(PIBLASTER_FILE, "w");
	if (file == NULL) {
		writeLog(lockOpener.logFile, lockOpener.name, WARNING, "Failed to open /dev/pi-blaster");
		safeExit();
	}
	return file;
}

// Turn the servo, in percentage from 0 to 1
void setServoPosition(FILE* piblaster, double percentage) {
	if (percentage < 0 || percentage > 1) {
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "Set Servo Position must be between 0 and 1");
		safeExit();
	}

	//printf("Setting Servo Position:\n%d=%f (Percentage: %f)\n", SERVOPIN, SERVOMIN + ((SERVOMAX - SERVOMIN) * percentage), percentage);
	fprintf(piblaster, "%d=%f\n", SERVOPIN, SERVOMIN + ((SERVOMAX - SERVOMIN) * percentage));
	fflush(piblaster);
	usleep(1000000);
}

#endif