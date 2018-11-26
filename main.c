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
	sqlite3_stmt *stmt;
	char* zErrMsg;
};

void testStepper(GPIO_Handle gpio);
void testServo(FILE* file);

static int gotCombo(void *cbArgs, int argc, char **argv, char **azColName) {
	printf("Sup!");
	return 0;
}

static int commandsQueued(void *cbArgs, int argc, char **argv, char **azColName) {
	char* data = 0;
	char query[1024];

	// Parse DB Data
	printf("Command Recieved:\n");
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		if (!strncmp(azColName[i], "data", 4)) {
			data = argv[i];
		}
	}

	// Update DB
	strcpy(query, "");
	strcat(query, "UPDATE commands SET completed = 1 WHERE completed = 0;");
	printf("%s", query);
	if (sqlite3_exec(((struct LockOpener*) cbArgs)->db, query, 0, 0, &(((struct LockOpener*) cbArgs)->zErrMsg)) != SQLITE_OK) {
		errorMessage(ERR_DATABASE_QUERY_FAILED);
	}

	// Get Combo for lock with ID
	strcpy(query, "");
	strcat(query, "SELECT * FROM data WHERE id = ");
	strcat(query, data);
	strcat(query, ";");
	printf("%s", query);
	if (sqlite3_exec(((struct LockOpener*) cbArgs)->db, query, gotCombo, cbArgs, &(((struct LockOpener*) cbArgs)->zErrMsg)) != SQLITE_OK) {
		errorMessage(ERR_DATABASE_QUERY_FAILED);
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
		char* query = "SELECT * FROM commands WHERE completed = 0;";
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