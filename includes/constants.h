#ifndef LOCKOPENER_CONSTS_H
#define LOCKOPENER_CONSTS_H

#include "../gpio/gpiolib_reg.h"

enum ERROR {INFO, DEBUG, WARNING, ERROR, CRITICAL};
const char errDesc[5][12] = { "Info", "Debug", "Warning", "Error", "Critical"};

const char* SQLITE_DB = "site/database/db.db3";

const int LOCK_STEPPER = 0;
const int UNLOCKER_STEPPER = 1;

struct LockOpener {
	// GPIO
	GPIO_Handle gpio;
	FILE* piBlaster;

	// SQLite3
	sqlite3* db;
	sqlite3_stmt *stmt;
	char* zErrMsg;

	// Log File
	FILE* logFile;
	// Program Name
	char* name;
	// Max Lock Number
	int maxNum;

	//Watchdog File Descriptor
	int watchDog;
	int watchDogTimer;

} lockOpener;

#endif