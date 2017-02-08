#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>


#define SENSOR_NAME "/sys/bus/w1/devices/28-000006b4acf6/w1_slave"

static double read_temp(char *filename) {

	double temp;
	char string1 [4], string2 [8];


	FILE *fff;									//creates pointer to file
	fff=fopen(filename, "r");							//points fff to device file
	if(fff <=0){									//checks to see if opened correctly
		printf("File not opened");
		return 999;
	}
	fscanf(fff, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s", string1);		//scans YES value of line 1
	if(!strcmp(string1,"YES")){							//checks YES value
		fscanf(fff, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %s", string2);		//scans temp value
		temp=atoi(string2+2);							//skips "t=" and converts to integer
		temp/=1000;								//converts from milliCelcius to Celcius
		return temp;
	} 
	else{
	return 999;
	}
}

int main(int argc, char **argv) {

	double temp1;

	while(1) {

		temp1=read_temp(SENSOR_NAME);						//sets temp1 to interger value returned from read_temp()
		if (temp1 == 999){							//checks for error
			printf("ERROR");
			return 0;
		}
		else{
			printf("%.2lfC\n",temp1);					//prints temperature value in C
		}
	}
	sleep(1);									//waits one second
	return 0;
}
