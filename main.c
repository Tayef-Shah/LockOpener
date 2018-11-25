#include <stdio.h>

#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"

#include "gpio/stepper_motor.h"
#include "gpio/servo_motor.h"

#include "includes/constants.h"

void testStepper(GPIO_Handle gpio);
void testServo(FILE* file);
int main() {

    //Initialize the GPIO pins
    GPIO_Handle gpio = initializeGPIO();

	//Initialize Pi-Blaster file
	FILE* piBlaster = fopen(PIBLASTER_FILE, "w");

	//Initialize Stepper Motor
	stepperInit(gpio);

	//Testing
	testStepper(gpio);
	usleep(1000000);
	testServo(piBlaster);
	usleep(1000000);

    return 0;
}

// Spin Stepper Motor 180 Degrees
void testStepper(GPIO_Handle gpio) {
	//Testing for stepper motor
	for (int i = 0; i < 512; ++i) {
		stepStepperOnce(gpio, 1);
	}

	// Reset GPIO Pins
	for (int i = 0; i < 4; ++i)
		outputOff(gpio, STEPPER_PIN[i]);
}

// Set servo to max, sleep 1 second, then set it to min
void testServo(FILE* file) {
	setServoPosition(file, 1);
	usleep(10000000);
	setServoPosition(file, 0);
}