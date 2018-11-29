#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "../sqlite3.h"
#include "includes/constants.h"

#include "gpio/gpiolib_addr.h"
#include "gpio/gpiolib_reg.h"
#include "gpio/gpio_helper.h"

#include "gpio/stepper_motor.h"
#include "gpio/servo_motor.h"

#include "includes/combo.h"
#include "includes/log.h"
#include "includes/testing.h"
#include "includes/watchdog.h"


// Turn off GPIO then exit
void safeExit() {
	stepperOff(lockOpener.gpio);
	exit(-1);
}

// Handles Ctrl-C and exit
void sig_handler(int signo) {
	if (signo == SIGINT || signo == SIGTERM) {
		writeLog(lockOpener.logFile, lockOpener.name, WARNING, "Program Exited (by Ctrl-C or systemd)!.");
		stopWatchDog();
		safeExit();
	}
}

static int gotCombo(void *cbArgs, int argc, char **argv, char **azColName) {
	int num1 = -1, num2 = -1, num3 = -1;

	//Parse Combination
	char gotCombo[1024];
	strcpy(gotCombo, "Got Combo: ");
	for (int i = 0; i < argc; i++) {

		// Log DB Query
		char rowData[128];
		snprintf(rowData, 128, "(%s = %s) ", azColName[i], argv[i] ? argv[i] : "NULL");
		strcat(gotCombo, rowData);

		// Get Combination Data
		if (!strncmp(azColName[i], "num1", 4)) {
			num1 = (int)strtol(argv[i], (char **)NULL, 10);
		} else if (!strncmp(azColName[i], "num2", 4)) {
			num2 = (int)strtol(argv[i], (char **)NULL, 10);
		} else if (!strncmp(azColName[i], "num3", 4)) {
			num3 = (int)strtol(argv[i], (char **)NULL, 10);
		}
	}
	writeLog(lockOpener.logFile, lockOpener.name, INFO, gotCombo);

	// Log Parsed Lock Combination
	char parseDB[1024];
	snprintf(parseDB, 1024, "Parsed: %d - %d - %d", num1, num2, num3);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, parseDB);

	// Do Lock opening sequence
	turn(lockOpener.gpio, lockOpener.maxNum, num1, num2, num3);
	unlock(lockOpener.gpio);
	reset(lockOpener.gpio, num3, lockOpener.maxNum);

	// Log Completion
	writeLog(lockOpener.logFile, lockOpener.name, INFO, "Done Combination Sequence!");

	return 0;
}

static int commandsQueued(void *cbArgs, int argc, char **argv, char **azColName) {
	char* commandID = 0;
	char* data = 0;
	char query[1024];

	// Parse DB Data
	char cmdRecieved[1024];
	strcpy(cmdRecieved, "Command Recieved: ");
	for (int i = 0; i < argc; i++) {

		// Log DB Query
		char rowData[128];
		snprintf(rowData, 128, "(%s = %s) ", azColName[i], argv[i] ? argv[i] : "NULL");
		strcat(cmdRecieved, rowData);

		// Get Lock ID data
		if (!strncmp(azColName[i], "data", 4)) {
			data = argv[i];
		} else if (!strncmp(azColName[i], "id", 2)) {
			commandID = argv[i];
		}
	}
	writeLog(lockOpener.logFile, lockOpener.name, INFO, cmdRecieved);

	// Update DB
	strcpy(query, "");
	strcat(query, "UPDATE commands SET completed = 1 WHERE id = ");
	strcat(query, commandID);
	strcat(query, ";");

	// Log DB Query
	char queryBuffer[2048];
	strcpy(queryBuffer, "SQLite3: [Query] ");
	strcat(queryBuffer, query);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, queryBuffer);

	// Execute DB Query
	if (sqlite3_exec(lockOpener.db, query, 0, 0, &(lockOpener.zErrMsg)) != SQLITE_OK) {
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "SQLite3: Database Query Failed!");
		safeExit();
	}

	// Get Combo for lock with ID
	strcpy(query, "");
	strcat(query, "SELECT * FROM data WHERE id = ");
	strcat(query, data);
	strcat(query, ";");

	// Log DB Query
	strcpy(queryBuffer, "");
	strcat(queryBuffer, "SQLite3: [Query] ");
	strcat(queryBuffer, query);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, queryBuffer);

	// Execute DB Query
	if (sqlite3_exec(lockOpener.db, query, gotCombo, cbArgs, &(lockOpener.zErrMsg)) != SQLITE_OK) {
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "SQLite3: Database Query Failed!");
		safeExit();
	}

	return 0;
}

int main(int argc, const char* const argv[]) {
	//Initialize Log File
	lockOpener.logFile = initLogFile();

    //Initialize the GPIO pins
	lockOpener.gpio = initializeGPIO();

	//Initialize Pi-Blaster file
	//lockOpener.piBlaster = servoInit();

	//Initialize Stepper Motor
	stepperInit(lockOpener.gpio);

	//Get Program Name
	lockOpener.name = getProgramName(argv);

	//Start Program
	lockOpener.maxNum = getLockMax(lockOpener.name);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, "System Started!");

	//Start Watchdog
	lockOpener.watchDog = initWatchDog();

	//Ping Watchdog
	pthread_t tid;
	pthread_create(&tid, NULL, pingWatchDog, (void *)&tid);

	//Handle Ctrl-C
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		writeLog(lockOpener.logFile, lockOpener.name, ERROR, "Failed to initialize sig_handler!");
		safeExit();
	}

	// Run Program
	while (1) {
		//Initialize SQLite DB
		lockOpener.zErrMsg = 0;
		if (sqlite3_open(SQLITE_DB, &(lockOpener.db))) {
			writeLog(lockOpener.logFile, lockOpener.name, ERROR, "SQLite3: Failed to open database!");
			safeExit();
		}

		// Check DB for commands
		char* query = "SELECT * FROM commands WHERE completed = 0;";
		if (sqlite3_exec(lockOpener.db, query, commandsQueued, &lockOpener, &(lockOpener.zErrMsg)) != SQLITE_OK) {
			writeLog(lockOpener.logFile, lockOpener.name, ERROR, "SQLite3: Database Query Failed!");
			safeExit();
		}
		sqlite3_close(lockOpener.db);
		usleep(1000000);
	}

    return 0;
}