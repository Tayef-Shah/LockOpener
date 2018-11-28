#ifndef COMBO_H
#define COMBO_H

#include <math.h>
#include <stdlib.h>
#include "stepper_motor.h"
#include "servo_motor.h"

// [Deprecated] Adjustment Factor
// const float LOCK_ADJ = 0.5;

int rotate(GPIO_Handle gpio, int ticks, int max){  //Argument is in the degrees of the lock
    int stepDegree = (int) ((512/(double)max) * (abs(ticks)));
	printf("Rotate: %d Steps\n", stepDegree);
    for(int i = 0; i < stepDegree; ++i){
        stepStepperOnce(gpio, ticks < 0 ? -1 : 1, max == 1 ? UNLOCKER_STEPPER : LOCK_STEPPER);
    }
    return ticks < 0 ? -stepDegree : stepDegree;
}

int turn(GPIO_Handle gpio, int max, int first, int second, int third){
	int totalRotations = 0;

	//Motor turns closewise looking directly at it
	printf("Started Turning:\n");
	fflush(stdout);

    if(first < 0 || second < 0 || third < 0 || max < 0){    //Argument check for NO NEGATIVE arguments
        return -1;
    }
    if(first > max || second > max || third > max){         //Argument BOUNDS checks for MAX BOUNDS
        return -2;
    }

    //CCW looking directly at motor
	printf("Rotate (Num1): %d\n", -(2* max + (max-first)));
	fflush(stdout);
	totalRotations += rotate(gpio, -(2 * max + (max - first)), max);             //First rotation to first number, SETS to zero 
	usleep(1000000);

    //(CW) Second rotation to second number, SETS to zero
	printf("Rotate (Num2): %d\n", max);
	fflush(stdout);
	totalRotations += rotate(gpio, max, max);
    if(first > second){
		printf("Rotate: %d\n", max - first + second);
		fflush(stdout);
		totalRotations += rotate(gpio, max-first+second, max);
    } else {
		printf("Rotate: %d\n", second-first);
		fflush(stdout);
		totalRotations += rotate(gpio, second - first, max);
    }
	usleep(1000000);
	
    //Roatation to last number
    if(second < third) {
		printf("Rotate (Num3): %d\n", -(max - (third - second)));
		fflush(stdout);
		totalRotations += rotate(gpio, -(max-(third-second)), max);
    } else {
		printf("Rotate (Num3): %d\n", -(second - third));
		fflush(stdout);
		totalRotations += rotate(gpio, -(second - third), max);
    }
	usleep(1000000);

    return totalRotations;
}

//Brings lock back to zero based on the final number it lands on
int reset(GPIO_Handle gpio, int num, int max){
	printf("Rotate (Reseting to zero): %d\n", -num);
	fflush(stdout);
	rotate(gpio, -num - 1, max);
	//for (int i = 0; i < abs(num) + (1 * (512.0 / 40.0)); ++i) {
	//	stepStepperOnce(gpio, -num < 0 ? -1 : 1, LOCK_STEPPER);
	//}
	//rotate(gpio, 1, max);
	stepperOff(gpio);
	usleep(1000000);
}

// [Deprecated] Turns the servo motor
int pull(FILE* piblaster){
	printf("Started Servo (Down)\n");
	fflush(stdout);
	setServoPosition(piblaster, 0);
	printf("Started Servo (Up)\n");
	fflush(stdout);
	setServoPosition(piblaster, 1);
	usleep(1000000);
    //how to check if it didn't work?
    return 0;
}

int unlock(GPIO_Handle gpio) {
	printf("Unlocking...\n");
	fflush(stdout);
	rotate(gpio, 2, 1);
	usleep(1000000);

	printf("Reseting...\n");
	fflush(stdout);
	rotate(gpio, -2, 1);
	usleep(1000000);
}

#endif