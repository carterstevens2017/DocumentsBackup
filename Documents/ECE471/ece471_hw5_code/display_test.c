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
if (fd == -1) fprintf(stderr, "Error opening file\n");	//if file doesn't open, error


/* Set slave address */

result=ioctl(fd, I2C_SLAVE, 0x70);			//sets slave address
if (result < 0) fprintf(stderr, "Error Addressing\n"); //if address is not correct, error


/* Turn on oscillator */

buffer[0] = (0x2<<4) | (0x01);
result=write(fd, buffer, 1);


/* Turn on Display, No Blink */

buffer[0] = (0x8<<4 | 0x1);
result=write(fd, buffer, 2);


/* Set Brightness */

buffer[0] = (0xE<<4 | 0xC);
result=write(fd, buffer, 2);

/* Write 1s to all Display Columns */

int i;

buffer[0] = 0x00;
for (i=0;i<16;i++) buffer[1+i]=0xff;
write(fd,buffer,17);


/* Close device */

close(fd);


return 0;
}