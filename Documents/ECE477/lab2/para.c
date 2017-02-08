#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int help(void);
int processor(void);

int main(int argc, char *argv[]){

	int i, prval;
	FILE *cpu;

//	printf("argc=%d\n",argc);

	/*Check if there are arguments*/
	if(argc == 1){
		help();
		return 0;
	}
	/*Checks for -h option*/
	for(i=0; i<argc; i++){
		if (strcmp(argv[i],"-h")==0){
			help();
			return 0;
		}
	}
	/*Checks for -p option*/
	for(i=0; i<argc; i++){
		if (strcmp(argv[i],"-p")==0){
			prval = processor();
			printf("This machine has %d processors\n", prval);
			return 0;
		}
	}
	fclose(cpu);
	return 0;
}

int help(void){
	printf("Help needed\n");
	return 0;
}

int processor(void){
	char *str;
	int processors = 0;
	FILE *cpu;

	str = (char *) malloc(100*sizeof(char));	

	cpu = fopen("/proc/cpuinfo", "r");

	if (cpu == NULL){
		printf("ERROR opening file");
		return -1;
	}
	while(!feof(cpu)){
		fgets(str, 100, cpu);
		if (strstr(str, "processor") != NULL){
			processors += 1;
		}
	}
	fclose(cpu);
	return processors;
}
