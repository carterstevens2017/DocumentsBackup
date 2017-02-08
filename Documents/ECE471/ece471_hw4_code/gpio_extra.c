#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>


int main(int argc, char **argv) {
int fd=1;
int i=0;

char buffer[10];					//creates string to copy fd values to and from
fd=open("/sys/class/gpio/export", O_WRONLY);		
if (fd<0) fprintf(stderr, "\tError_enabling\n");
strcpy(buffer, "4");					//enables GPIO4 
write(fd, buffer, 2);
close(fd);

fd=open("/sys/class/gpio/gpio4/direction", O_WRONLY);	//sets GPIO4 to output
if (fd<0) fprintf(stderr, "Error! \n");
write(fd,"out",2);
close(fd);

while(1){						//keeps LED blinkng indefinitely
	for(i=0; i<3; i++){
		fd=open("/sys/class/gpio/gpio4/value",O_WRONLY);	//sets GPIO4 HIGH
		if (fd<0) fprintf(stderr,"Error_writing!\n");
		write(fd,"1",1);
		close(fd);
	
		usleep(300*1000);
					//turns off process for 500ms

		fd=open("/sys/class/gpio/gpio4/value",O_WRONLY);	//sets GPIO4 LOW
		if (fd<0) fprintf(stderr,"Error_writing!\n");		
		write(fd,"0",1);
		close(fd);

		usleep(300*1000);
	}

	for(i=0; i<3; i++){
		fd=open("/sys/class/gpio/gpio4/value",O_WRONLY);	//sets GPIO4 HIGH
		if (fd<0) fprintf(stderr,"Error_writing!\n");
		write(fd,"1",1);
		close(fd);
		
		usleep(700*1000);
					//turns off process for 500ms
	
		fd=open("/sys/class/gpio/gpio4/value",O_WRONLY);	//sets GPIO4 LOW
		if (fd<0) fprintf(stderr,"Error_writing!\n");		
		write(fd,"0",1);
		close(fd);

		usleep(300*1000);
	}					//turns off process for 500ms
}
}
