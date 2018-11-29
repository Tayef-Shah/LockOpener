#ifndef LOCKOPENER_TESTING_H
#define LOCKOPENER_TESTING_H

// Spin Stepper Motor 180 Degrees
void testStepper(GPIO_Handle gpio) {
	//Testing for stepper motor
	for (int i = 0; i < 512 / 4; i++) {
		stepStepperOnce(gpio, -1, 1);
	}
	stepperOff(gpio);
}

// Set servo to max, sleep 2 second, then set it to min
void testServo(FILE* file) {
	setServoPosition(file, 1);
	usleep(2000000);
	setServoPosition(file, 0);
}

#endif