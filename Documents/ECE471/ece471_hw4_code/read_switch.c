#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>


int main(int argc, char **argv) {
int fd;

char buffer[10];
fd=open("/sys/class/gpio/export", O_WRONLY);		//enables GPIO17
if (fd<0) fprintf(stderr, "\tError_enabling\n");
strcpy(buffer, "17");					
write(fd, buffer, 2);
close(fd);

fd=open("/sys/class/gpio/gpio17/direction", O_WRONLY);	//sets GPIO17 to input
if (fd<0) fprintf(stderr, "Error! \n");
write(fd,"in",2);
close(fd);

while(1){
fd=open("/sys/class/gpio/gpio17/value", O_WRONLY);	//reads input of GPIO17
if (fd<0) fprintf(stderr, "Error_reading!\n");
read(fd,buffer,1);
close(fd);

if (fd>0) fprintf(stderr, "Switch Closed!\n");		//Prints message if GPIO is HIGH
usleep(500*1000);
}
	

}
