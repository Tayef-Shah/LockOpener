#include <math.h>

void rotate(int degs){
    int degress = 360/degs;
}

int turn(int max, int first, int second, int third){

    if(first < 0 || second < 0 || third < 0 || max < 0){    //Argument check for NO NEGATIVE arguments
        return -1;
    }
    if(first > max || second > max || third > max){         //Argument BOUNDS checks for MAX BOUNDS
        return -2;
    }

    //Motor turns closewise looking directly at it

    //First rotation to first number, SETS to zero 
    //CCW looking directly at motor
    rotate(2*max + first);
    rotate(-first);
    //Second rotation to second number, SETS to zero
    //CW
    rotate(-(max-second));
    rotate(max-second);
    //Rotation to last number
    rotate(third);
    //Run servo motor procedure (up, hold, down)
    //SET to zero
    rotate(-third);

    return 0;
}