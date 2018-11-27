/*
extra ideas:
-have multiple locks for config
	-lock 1, lock 2 for user to choose
	
NOTE: check getProgramName, might have to put in main
*/

/*
set time[] fro getTime to 30
log: FILE*, char* time[30], Error, "method: detail");
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

//types of errors
enum Error{SUCCESS, INPUT, OUTPUT, ARGUMENT, TIMEOUT};

void getTime(char* sysTime);
char* getProgramName();
void writeFile(char name [], char word []);
void writeLog(FILE* log, char* time, Error error, char detail []);
char* readFile(char name []);
int startUp(time_t start);

//get time of day, takes in a char pointer (char []) for storing time, calls everytime when needed
void getTime(char* sysTime){
	struct timeval tv;
	time_t current;
	
	gettimeofday(&tv, NULL);
	current = tv.tv_sec;

	//MM-DD-YYYY HH:MM:SS
  	strftime(sysTime,30,"%m-%d-%Y  %T.",localtime(&current));
} 

char* getProgramName(const int argc, const char* const argv[]){
	//made string storing ./programName
	const char* argName = argv [0];
	
	//finds the length of argv[0]
	int i = 0, nameLength = 0;
	while(argName[i] != 0){
		++nameLength;
		++i;
	}
	
	//stores char[] programName without ./
	char progName[nameLength];
	for(int j = 0; j < i-2; ++j){
		progName[j] = argName[j+2];
	}
	return progName;
}

//write to any file, takes in file name and what to write
void writeFile(char name [], char word []){
	FILE* fprt = fopen("/" + *name, "a");
	
	fprintf(fprt, "%s", word);
	fclose(fprt);
}

//write to log, takes in time, type of error, and detail of log entry
void writeLog(FILE* log, char* time, Error error, char detail []) {	
	getTime(time);
	fprintf(log, "%s : %s : %d : %s", time, getProgramName(),  error, detail);
	fclose(log);
}

//read any file and returns what is being read
char* readFile(char name []){
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
}

//creats log and config, takes in time for log
int startUp(char* start){
	//time_t start = time(NULL);
	FILE* log;
	FILE* config;
	
	char input[1024];
	
	log = fopen("/log", "a");
	config = fopen("/data", "r");
	
	
	if(!log){
		perror("can not open log");
		return -1;
	}
	
	if(!config){
		perror("can not open config");
		writeLog(log, start,INPUT, "config: file does not exist\n");
		return -1;
	}else{
		fgets(input, 1024, config);
		fclose(config);
		writeLog(log, start, SUCCESS, "config: input [] is initialized\n");
	}
	
	return 0;
}

#endif //Config.h