#ifndef LOCKOPENER_CONSTS_H
#define LOCKOPENER_CONSTS_H

// Define constants for Error codes
#define ERR_TOO_LITTLE_ARGS 1
#define ERR_UNKNOWN 2
#define ERR_GPIO_FAILED 3
#define ERR_INVALID_PIN 4

// Program Constants
const int stepperPin[4] = {17, 22, 23, 24};
const int stepperSeq[8][4] = { {1,0,0,1},
                             {1,0,0,0},
                             {1,1,0,0},
                             {0,1,0,0},
                             {0,1,1,0},
                             {0,0,1,0},
                             {0,0,1,1},
                             {0,0,0,1} };

#endif