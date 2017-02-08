#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

int main(int argc, char **argv) {

int fd, result;

char i2c_device[]="/sys/bus/i2c-1";

unsigned char buffer[17];

/* Open i2c device */

fd = open("/dev/i2c-1", O_RDWR);			//opens device file
if (fd == -1) fprintf(stderr, "Error Opening!\n");	//if file doesn't open, error


/* Set slave address */

result=ioctl(fd, I2C_SLAVE, 0x70);			    //sets slave address
if (result < 0) fprintf(stderr, "Error Slave Address!\n"); //of address os mpt correct, error


/* Turn on oscillator */

buffer[0] = (0x2<<4) | (0x01);
result=write(fd, buffer, 1);


/* Turn on Display, No Blink */

buffer[0] = (0x8<<4 | 0x1);
result=write(fd, buffer, 2);


/* Set Brightness */

buffer[0] = (0xE<<4 | 0xC);
result=write(fd, buffer, 2);

while (1) { 

/* Writing message */

int i;
/* LED columns found in buffer[1,3,7,9] */
buffer[0] = 0x00;
buffer[1] = 0x79; // Write the letter E
buffer[2] = 0x00;
buffer[3] = 0x39; // Write the letter C
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x79; // Write the letter E
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(1000*1000);	//wait 1s

/* Writing Numbers */

buffer[0] = 0x00;
buffer[1] = 0x66; // Write the number 4 
buffer[2] = 0x00;
buffer[3] = 0x07; // Write the number 7 
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x06; // Write the number 1 
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(1000*1000);

}

/* Close device */

close(fd);


return 0;
}