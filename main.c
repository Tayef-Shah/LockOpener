#include <stdio.h>
#include <string.h>

#include "includes/sqlite3.h"

#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"

#include "gpio/stepper_motor.h"
#include "gpio/servo_motor.h"

#include "includes/constants.h"

struct LockOpener {
	GPIO_Handle gpio;
	FILE* piBlaster;
	sqlite3* db;
	char* zErrMsg;
};

void testStepper(GPIO_Handle gpio);
void testServo(FILE* file);

static int commandsQueued(void *cbArgs, int argc, char **argv, char **azColName) {
	for (int i = 0; i < argc; i++) {
		if (!strncmp(azColName[i], "completed", 9)) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

			//Testing
			printf("Starting in 3 seconds...\n");
			usleep(3000000);

			testStepper(((struct LockOpener*) cbArgs)->gpio);
			usleep(1000000);
			testServo(((struct LockOpener*) cbArgs)->piBlaster);
			usleep(1000000);
		}
	}
	return 0;
}

int main() {
	struct LockOpener lockOpener;

    //Initialize the GPIO pins
	lockOpener.gpio = initializeGPIO();

	//Initialize Pi-Blaster file
	lockOpener.piBlaster = servoInit();

	//Initialize Stepper Motor
	stepperInit(lockOpener.gpio);

	// Program
	while (1) {
		//Initialize SQLite DB
		lockOpener.zErrMsg = 0;
		if (sqlite3_open(SQLITE_DB, &(lockOpener.db))) {
			errorMessage(ERR_DATABASE_OPEN_FAILED);
		}
		// Check DB for commands
		char* query = "SELECT * FROM commands WHERE completed == 0;";
		if (sqlite3_exec(lockOpener.db, query, commandsQueued, &lockOpener, &(lockOpener.zErrMsg)) != SQLITE_OK) {
			errorMessage(ERR_DATABASE_QUERY_FAILED);
		}
		sqlite3_close(lockOpener.db);
		usleep(1000000);
	}

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

// Set servo to max, sleep 2 second, then set it to min
void testServo(FILE* file) {
	setServoPosition(file, 1);
	usleep(2000000);
	setServoPosition(file, 0);
}