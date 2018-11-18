#ifndef GPIO_HELPER_H
#define GPIO_HELPER_H

#include <stdlib.h>
#include <stdio.h>

#include "../constants.h"

//Output error message and exit
void errorMessage(const int errorCode)
{
    fprintf(stderr, "An error occured; the error code was %d \n", errorCode);
    exit(-1);
}

//Initialize the GPIO pins
GPIO_Handle initializeGPIO()
{
    GPIO_Handle gpio = gpiolib_init_gpio();
    // Check if the GPIO was initialized correctly
    if (gpio == NULL) 
        errorMessage(ERR_GPIO_FAILED);
    return gpio;
}

//Change the passed in pin value in the select register to function as output (for debug LED's)
void setToOutput(GPIO_Handle gpio, int gpioNum) 
{
    //Check that the gpio is functional
    if (gpio == NULL)
        errorMessage(ERR_GPIO_FAILED);

    //Check that we are trying to set a valid pin number
    //If not, output the corresponding error message
    if (gpioNum < 2 || gpioNum > 27)
        errorMessage(ERR_INVALID_PIN);

    //Find the register number for that corresponding pin
    int registerNum = gpioNum / 10;

    //Find the amount to bit shift to set the pin to output
    int bitShift = (gpioNum % 10) * 3;

    //Apply the bitshift to the select register
    uint32_t sel_reg = gpiolib_read_reg(gpio, GPFSEL(registerNum));
    sel_reg |= 1 << bitShift;
    gpiolib_write_reg(gpio, GPFSEL(registerNum), sel_reg);
}

//Set the pin output to turn on
void outputOn(GPIO_Handle gpio, int gpioNum)
{
    gpiolib_write_reg(gpio, GPSET(0), 1 << gpioNum);
}

//Set the pin output to turn off
void outputOff(GPIO_Handle gpio, int gpioNum)
{
    gpiolib_write_reg(gpio, GPCLR(0), 1 << gpioNum);
}

//Get pin state
//Returns true if the pin at gpioNum is ON
int getState(GPIO_Handle gpio, int gpioNum)
{
    //If the GPIO was not properly initialized, print and exit program
    if (gpio == NULL)
        errorMessage(ERR_GPIO_FAILED);

    //Read the GPIO states
    uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));
    //Based on the passed in diode number, check that specific GPIO pin
    return !(level_reg & (1 << gpioNum));
}

#endif