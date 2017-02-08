#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define LENGTH 3


int main(int argc, char **argv) {

        int spi_fd;
        double value;
	double deg_c;
        int result;
	int mode=SPI_MODE_0;
	struct spi_ioc_transfer spi;
	float vcc=3.3;
	unsigned char data_out[LENGTH]={0x1,0x2,0x3};
	unsigned char data_in[LENGTH];
	int bits_per_transfer = 0;
	int clock_speed = 100;

	memset(&spi, 0, sizeof (struct spi_ioc_transfer));

	spi.tx_buf = (unsigned long)&data_out;
	spi.rx_buf = (unsigned long)&data_in;
	spi.len    = LENGTH;
	spi.delay_usecs = 0;
	spi.speed_hz    = 100000;
	spi.bits_per_word = 8;
	spi.cs_change   = 0;

	/* Open SPI device */
	spi_fd=open("/dev/spidev0.0", O_RDWR);
	if(spi_fd<0)
		{printf("error opening file \n");
	}

	/* Set SPI Mode_0 */
	result=ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
	if (spi_fd<0){
		printf("error setting mode \n");
	}

	/* Set 8 bits per word */
	result=ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_transfer);
	if (spi_fd<0){
		printf("error setting bits per word \n");
	}

	/* Set 100 kHz max frequency */
	result=ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &clock_speed);
	if (spi_fd<0){
		printf("error setting max speed \n");
	}

	/* Loop forever printing the CH0 and CH1 Voltages 	*/
	/* Once per second.*/

	while(1){
	data_out[0]=(0x01);
	data_out[1]=(0x90);
	data_out[2]=(0x00);
	result=ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi);
	if(result<0){
		printf("error for ioctl on ch2");
	}
	value= (data_in[1]<<8)+data_in[2];
	value= (value*vcc)/1024;
	deg_c= (value*100)-50;
	
	printf("It is %f degrees Celsius\n", deg_c);

	usleep(1000000);
	}

	return 0;
}
