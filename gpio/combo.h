#ifndef COMBO_H
#define COMBO_H

#include <math.h>
#include "stepper_motor.h"
#include "servo_motor.h"


int rotate(GPIO_Handle gpio, int degs, int max){  //Argument is in the degrees of the lock
    int stepDegree = (512/max)*degs;
    if(stepDegree < 0 || stepDegree > max){
        return - 1; //Arugment error
    }
    for(int i = 0; i < stepDegree; ++i){
        stepStepperOnce(gpio, 1);
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
    rotate(gpio, -(2 * max + first) , max);             //First rotation to first number, SETS to zero 
	printf("Rotate: %d\n", -(2 * max + first));
	fflush(stdout);
    
    //(CW) Second rotation to second number, SETS to zero
    rotate(gpio, max, max);
	printf("Rotate: %d\n", max);
	fflush(stdout);
    if(first > second){
        rotate(gpio, first-second, max);
		printf("Rotate: %d\n", first - second);
		fflush(stdout);
    } else {
        rotate(gpio, first, max);
		printf("Rotate: %d\n", first);
		fflush(stdout);
        rotate(gpio, max-second, max);
		printf("Rotate: %d\n", max - second);
		fflush(stdout);
    }

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

    return 0;
}

//Brings lock back to zero based on the final number it lands on
int reset(GPIO_Handle gpio, int starting, int max){
    if(starting < 0){
        return -1;
    }
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