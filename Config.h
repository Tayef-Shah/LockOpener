/*
extra ideas:
-have multiple locks for config
	-lock 1, lock 2 for user to choose
*/

/*
detail: function name: what it is
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <time.h>

using namespace std;

//types of errors
enum Error{SUCCESS, INPUT, OUTPUT, ARGUMENT, TIMEOUT};

//write to any file, takes in file name and what to write
void writeFile(char name [], char word []){
	FILE* fprt = fopen("/" + *name, "a");
	
	fprintf(fprt, "%s", word);
	fclose(fprt);
}

//write to log, takes in time, type of error, and detail of log entry
void writeLog(FILE* log, time_t time, Error error, char detail []) {
	fprintf(log, "%d, %d, %s", time, error, detail);
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
int startUp(time_t start){
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