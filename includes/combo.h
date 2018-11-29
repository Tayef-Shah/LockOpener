#ifndef COMBO_H
#define COMBO_H

#include <math.h>
#include <stdlib.h>

#include "../gpio/stepper_motor.h"
#include "../gpio/servo_motor.h"

// Rotate the lock, a specified number of ticks, given that the lock has max number of ticks
int rotate(GPIO_Handle gpio, int ticks, int max) {
	// Calculate motor steps
    int stepDegree = (int) ((512/(double)max) * (abs(ticks)));

	// Log Rotation Amount
	char logBuffer[512];
	snprintf(logBuffer, 512, "Rotate: %d Steps\n", stepDegree);
	writeLog(lockOpener.logFile, lockOpener.name, DEBUG, logBuffer);

	// Rotate Stepper Motor
    for(int i = 0; i < stepDegree; ++i){
        stepStepperOnce(gpio, ticks < 0 ? -1 : 1, max == 1 ? UNLOCKER_STEPPER : LOCK_STEPPER);
    }
    return ticks < 0 ? -stepDegree : stepDegree;
}

int turn(GPIO_Handle gpio, int max, int first, int second, int third){
	int totalRotations = 0;

	// Log Actions
	char logBuffer[512];
	writeLog(lockOpener.logFile, lockOpener.name, INFO, "Starting Turning!");

	//Motor turns closewise looking directly at it

    if(first < 0 || second < 0 || third < 0 || max < 0){    //Argument check for NO NEGATIVE arguments
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "In turn function, no numbers should be negative!");
		safeExit();
    }
    if(first > max || second > max || third > max){         //Argument BOUNDS checks for MAX BOUNDS
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "In turn function, no numbers should be greater than the lock maximum!");
		safeExit();
    }

    // Log Rotation
	snprintf(logBuffer, 512, "Rotate (Num1): %d\n", -(2* max + (max-first)));
	writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);

	//CCW looking directly at motor
	totalRotations += rotate(gpio, -(2 * max + (max - first)), max);             //First rotation to first number, SETS to zero 
	usleep(1000000);

    
	// Log Rotation
	snprintf(logBuffer, 512, "Rotate (Num2): %d\n", max);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);

	//(CW) Second rotation to second number, SETS to zero
	totalRotations += rotate(gpio, max, max);
    if(first > second){
		snprintf(logBuffer, 512, "Rotate: %d\n", max - first + second);
		writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);
		totalRotations += rotate(gpio, max-first+second, max);
    } else {
		snprintf(logBuffer, 512, "Rotate: %d\n", second-first);
		writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);
		totalRotations += rotate(gpio, second - first, max);
    }
	usleep(1000000);
	
    //Roatation to last number
    if(second < third) {
		snprintf(logBuffer, 512, "Rotate (Num3): %d\n", -(max - (third - second)));
		writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);
		totalRotations += rotate(gpio, -(max-(third-second)), max);
    } else {
		snprintf(logBuffer, 512, "Rotate (Num3): %d\n", -(second - third));
		writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);
		totalRotations += rotate(gpio, -(second - third), max);
    }
	usleep(1000000);

    return totalRotations;
}

//Brings lock back to zero based on the final number it lands on
int reset(GPIO_Handle gpio, int num, int max){
	// Log Reset Action
	char logBuffer[512];
	snprintf(logBuffer, 512, "Rotate (Reseting to zero): %d\n", -num);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, logBuffer);

	// Reset the lock turner to zero and turn off both steppers
	rotate(gpio, -num - 1, max);
	stepperOff(gpio);
	usleep(1000000);
}

// [Deprecated] Turns the servo motor
int pull(FILE* piblaster){
	writeLog(lockOpener.logFile, lockOpener.name, DEBUG, "Started Servo (Down)");
	setServoPosition(piblaster, 0);

	writeLog(lockOpener.logFile, lockOpener.name, DEBUG, "Started Servo (Up)");
	setServoPosition(piblaster, 1);
	usleep(1000000);
    //how to check if it didn't work?
    return 0;
}

int unlock(GPIO_Handle gpio) {
	writeLog(lockOpener.logFile, lockOpener.name, INFO, "Unlocking Lock");
	rotate(gpio, 2, 1);
	usleep(1000000);

	writeLog(lockOpener.logFile, lockOpener.name, INFO, "Resetting Unlocker");
	rotate(gpio, -2, 1);
	usleep(1000000);
}

#endif