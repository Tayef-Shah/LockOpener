#ifndef COMBO_H
#define COMBO_H

#include <math.h>
#include <stdlib.h>
#include "stepper_motor.h"
#include "servo_motor.h"


int rotate(GPIO_Handle gpio, int ticks, int max){  //Argument is in the degrees of the lock
    int stepDegree = (int) ((512/(double)max) * abs(ticks));
	printf("Rotate: %d Steps\n", stepDegree);
    for(int i = 0; i < stepDegree; ++i){
        stepStepperOnce(gpio, ticks < 0 ? -1 : 1);
    }
    return 0;
}

int turn(GPIO_Handle gpio, int max, int first, int second, int third){
	printf("Started Turning:\n");
	fflush(stdout);

    if(first < 0 || second < 0 || third < 0 || max < 0){    //Argument check for NO NEGATIVE arguments
        return -1;
    }
    if(first > max || second > max || third > max){         //Argument BOUNDS checks for MAX BOUNDS
        return -2;
    }

    //Motor turns closewise looking directly at it

    //CCW looking directly at motor
	printf("Rotate: %d Ticks\n", -(3 * max + (max-first)));
	fflush(stdout);
    rotate(gpio, -(3 * max + (max - first)), max);             //First rotation to first number, SETS to zero 

    //(CW) Second rotation to second number, SETS to zero
	printf("Rotate: %d\n", max);
	fflush(stdout);
    rotate(gpio, max, max);
    if(first > second){
		printf("Rotate: %d\n", max - first + second);
		fflush(stdout);
        rotate(gpio, max-first+second, max);
    } else {
		printf("Rotate: %d\n", second-first);
		fflush(stdout);
        rotate(gpio, second - first, max);
    }
		/*
    //Roatation to last number
    if(second > third) {
        rotate(gpio, max-(second-third), max);
		printf("Rotate: %d\n", max - (second - third));
		fflush(stdout);
    } else {
        rotate(gpio, third-second, max);
		printf("Rotate: %d\n", third - second);
		fflush(stdout);
    }
	*/
    return 0;
}

//Brings lock back to zero based on the final number it lands on
int reset(GPIO_Handle gpio, int starting, int max){
    if(starting < 0){
        return -1;
    }
	printf("Rotate: %d Ticks\n", starting);
	fflush(stdout);
    rotate(gpio, starting, max);

	// Reset GPIO Pins
	for (int i = 0; i < 4; ++i)
		outputOff(gpio, STEPPER_PIN[i]);
    return 0;
}

//Turns the servo motor
int pull(FILE* piblaster){
	setServoPosition(piblaster, 0);
    setServoPosition(piblaster, 1);
    //how to check if it didn't work?
    return 0;
}

#endif