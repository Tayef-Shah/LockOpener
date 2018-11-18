/*
extra ideas:
-have multiple locks for config
	-lock 1, lock 2 for user to choose
*/

/*
-int max
-int [] dig
*/
#include <stdio.h>
#include <time.h>

using namespace std;

enum Error{SUCCESS, INPUT, OUTPUT, ARGUMENT, TIMEOUT};
	
void writeLog(FILE* log, time_t time, Error error, char detail []) {
	fprintf(log, "%d, %d, %s", time, error, detail);
	fflush(log);
}
		
int main(){
	time_t start = time(NULL);
	FILE* log;
	FILE* config;
	
	char input[1024];
	Error error;
	
	log = fopen("/log", "a");
	config = fopen("/data", "r");
	
	if(!log){
		perror("can not open log");
		return -1;
	}
	
	if(!config){
		perror("can not open config");
		error = INPUT;
		writeLog(log, start,error, "config file does not exist\n");
		return -1;
	}else{
		fgets(input, 1024, config);
		fclose(config);
		error = SUCCESS;
		writeLog(log, start, error, "input [] is initialized\n");
	}
	
	return 0;
}