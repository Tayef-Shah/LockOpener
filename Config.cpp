/*
extra ideas:
-have multiple locks for config
	-lock 1, lock 2 for user to choose
*/

/*
-int max
-int dig123
*/
#include <iostream>
#include <math.h>

using namespace std;

struct Config{
	int max;
	int dig1;
	int dig2;
	int dig3;
};

void loadConfig(Config& config){
	
}

int main(){
	FILE* config;
	config = fopen("/data", "r");
	max = 
}