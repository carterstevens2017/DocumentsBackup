#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <wiringPi.h>
#include "lcd.h"
#include <stdint.h>


int main(void){
int i, j;
int fd;

char message1 [256];
char message2 [256];
char buffer1 [30];
char buffer2 [30];

struct tm *t;
time_t tim;

printf("Raspberry Pi LCD test program\n");

if (wiringPiSetup() == -1){
	exit(1);
}

fd = lcdInit(2, 16, 4, 26,19,13,6,5,11,0,0,0,0);

if (fd == -1){
	printf("lcdInit failed \n");
}

sleep(1);

lcdPosition(fd,0,0);
lcdPuts(fd,"Carter Stevens");

sleep(2);
}

