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
if (result < 0) fprintf(stderr, "Error Slave Address!\n"); //if address is not correct, error


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

/* Writing letters */

buffer[0] = 0x00;
buffer[1] = 0x01; /* Write stage 1 of letter C */
buffer[2] = 0x00;
buffer[3] = 0x00; /* Write stage 1 of letter A */
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x01; /* Write stage 1 of letter S */
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(250*1000); /* Wait a quarter second */

buffer[0] = 0x00;
buffer[1] = 0x60; /* Write stage 2 of letter C */
buffer[2] = 0x00;
buffer[3] = 0x23; /* Write stage 2 of letter A */
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x43; /* Write stage 2 of letter S */
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(250*1000);

buffer[0] = 0x00;
buffer[1] = 0x39; /* Write the letter C */
buffer[2] = 0x00;
buffer[3] = 0x77; /* Write the letter A */
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x6D; /* Write the letter S */
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(250*1000);

buffer[0] = 0x00;
buffer[1] = 0x50; /* Write the first stage of letter C drop */
buffer[2] = 0x00;
buffer[3] = 0x5C; /* Write the first stage of letter A drop */
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x58; /* Write the first stage of letter S drop */
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(250*1000);

buffer[0] = 0x00;
buffer[1] = 0x08; /* Write the final stage of letter C drop */
buffer[2] = 0x00;
buffer[3] = 0x08; /* Write the final stage of letter A drop */
buffer[4] = 0x00;
buffer[5] = 0x00;
buffer[6] = 0x00;
buffer[7] = 0x08; /* Write the final stage of letter S drop */
buffer[8] = 0x00;
buffer[9] = 0x00;
write(fd, buffer,17);

usleep(250*1000);

}

/* Close device */

close(fd);


return 0;
}