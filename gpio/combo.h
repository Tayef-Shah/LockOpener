#ifndef COMBO_H
#define COMBO_H

#include <math.h>
#include "stepper_motor.h"
#include "servo_motor.h"


int rotate(GPIO_Handle gpio, int degs, int max){  //Argument is in the degrees of the lock
    int stepDegree = (521/max)*degs;
    if(stepDegree < 0 || stepDegree > max){
        return - 1; //Arugment error
    }
    for(int i = 0; i < stepDegree; ++i){
        stepStepperOnce(gpio, 1);
    }
    return 0;
}

int turn(int max, int first, int second, int third){

    if(first < 0 || second < 0 || third < 0 || max < 0){    //Argument check for NO NEGATIVE arguments
        return -1;
    }
    if(first > max || second > max || third > max){         //Argument BOUNDS checks for MAX BOUNDS
        return -2;
    }

    //Motor turns closewise looking directly at it

    //CCW looking directly at motor
    rotate(-2*max + first , max);             //First rotation to first number, SETS to zero 
    
    //(CW) Second rotation to second number, SETS to zero
    rotate(max, max);
    if(first > second){
        rotate(first-second, max);
    } else {
        rotate(first, max);
        rotate(max-second, max);
    }

    //Roatation to last number
    if(second > third){
        rotate(max-(second-third) , max);
    } else {
        rotate(third-second , max);        
    }

    return 0;
}

//Brings lock back to zero based on the final number it lands on
int reset(int starting, int max){
    if(starting < 0){
        return -1;
    }
    rotate(starting, max);
    return 0;
}

//Turns the servo motor
int pull(){
    setServoPosition(1);
    //how to check if it didn't work?
    return 0;
}

#endif