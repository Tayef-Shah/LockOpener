#ifndef COMBO_LOG_H
#define COMBO_LOG_H

#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//get time of day, takes in a char pointer for storing time, calls everytime when needed
char* getTime() {
	char* timeStr = malloc(128);

	struct timeval tv;
	gettimeofday(&tv, NULL);

	//MM-DD-YYYY HH:MM:SS
	strftime(timeStr, 30, "%m-%d-%Y %T.", localtime(&(tv.tv_sec)));
	return timeStr;
}

char* getProgramName(const char* const argv[]){
	//finds the length of argv[0]
	int nameLength = 0, lastSlash = -1;
	while (argv[0][nameLength] != 0) {
		if (argv[0][nameLength] == '\\' || argv[0][nameLength] == '/')
			lastSlash = nameLength;
		nameLength++;
	}
	
	//stores char[] programName without leading path
	//that's everything before the slash
	char* progName = malloc(nameLength);
	for(int j = lastSlash; j < nameLength; ++j){
		progName[j - lastSlash] = argv[0][j];
	}
	return progName;
}

//write to log, takes in time, type of error, and detail of log entry
void writeLog(FILE* log, char* name, int error, char* detail) {
	fprintf(log, "%s : %s : sev=%d : %s\n", getTime(), name, errDesc[error], detail);
	fflush(log);
}

//creats log and config, takes in time for log
FILE* initLogFile(){
	FILE* log = fopen("logs/lockopener.log", "a");
	if(!log){
		errorMessage(ERR_FILE_OPEN_FAILED);
	}
	return log;
}

int getLockMax(char* name) {
	// Read from config file
	FILE* config = fopen("lock.config", "r");
	if (!config) {
		errorMessage(ERR_FILE_OPEN_FAILED);
	}
	char firstLine[8];
	fgets(firstLine, 8, config);
	int maxNum = atoi(firstLine);

	// Write to config read log file
	FILE* cfLog = fopen("logs/config_read.log", "a");
	if (!cfLog) {
		errorMessage(ERR_FILE_OPEN_FAILED);
	}

	char out[64];
	snprintf(out, 64, "Read from config file: maxNum=%d", maxNum);
	writeLog(cfLog, name, 0, out);
	fclose(cfLog);

	// Return the config file data
	return maxNum;
}

#endif