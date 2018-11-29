#ifndef COMBO_LOG_H
#define COMBO_LOG_H

#include "constants.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

//get time of day, takes in a char pointer (char []) for storing time, calls everytime when needed
char* getTime() {
	char* timeStr = malloc(128);

	struct timeval tv;
	gettimeofday(&tv, NULL);

	//MM-DD-YYYY HH:MM:SS
	strftime(timeStr, 30, "%m-%d-%Y  %T.", localtime(&(tv.tv_sec)));
}

char* getProgramName(const char* const argv[]){
	//finds the length of argv[0]
	int nameLength = 0, lastSlash = -1;
	while (argv[0][nameLength] != 0) {
		if (argv[0][nameLength] == '\\' || argv[0][nameLength++] == '/')
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

//write to any file, takes in file name and what to write
/*void writeFile(FILE* file, char* str){	
	fprintf(file, "%s", str);
}*/

//write to log, takes in time, type of error, and detail of log entry
void writeLog(FILE* log, char* name, int error, char* detail) {
	fprintf(log, "%s : %s : sev=%d : %s", getTime(), name, error, detail);
}

//read any file and returns what is being read
/*char* readFile(char name []){
	char input[1024];
	
	for(int i = 0; i < 1024; i++){
		input[i] = 0;
	}
	FILE* fprt = fopen("/" + *name, "r");
	if(fprt == NULL){
		return NULL;
	}
	
	fgets(input, 1024, fprt);
	fclose(fprt);
	return input;
}*/

//creats log and config, takes in time for log
FILE* initLogFile(){
	FILE* log = fopen("lockopener.log", "a");
	
	if(!log){
		errorMessage(ERR_FILE_OPEN_FAILED);
	}	
	return 0;
}

#endif