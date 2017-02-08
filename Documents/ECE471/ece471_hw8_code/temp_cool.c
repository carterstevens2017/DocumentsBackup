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
	fscanf(fff, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s", string1);		//scans YES value
	if(!strcmp(string1,"YES")){							//checks YES value
		fscanf(fff, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %s", string2);		//scans temp value
		temp=atoi(string2+2);							//skpis "t=" and converts to integer
		return temp;
	} 
	else{
	return 999;
	}
}

int main(int argc, char **argv) {

	double temp1;
	double tempc;
	double tempf;
	double tempk;

	while(1) {

		temp1=read_temp(SENSOR_NAME);						//sets temp11 to temp value
		tempc=temp1/1000;							//converts temp from milliCelsius to celcius
		tempk=tempc+273.15;							//converts celsius to kelvin
		tempf=(tempc*(1.8))+32;							//converts Celsius to Fahrenheit
		if (temp1 == 999){							//checks for error
			printf("ERROR");
			return 0;
		}
		else{
			printf("%.2lfC\n",tempc);					//prints temp in C
			printf("%.2lfK\n",tempk);					//prints temp in K
			printf("%.2lfF\n\n",tempf);					//prints temp in F
		}
	}
	sleep(1);									//waits 1 second
	return 0;
}
