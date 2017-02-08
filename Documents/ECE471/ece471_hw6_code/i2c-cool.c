#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

/* Default i2c GPIO output pins on Raspberry-Pi */
#define SDA_GPIO	2
#define SCL_GPIO	3

/* Global variables */
static int scl_fd,sda_fd;

/* Advance Function declarations */
static int gpio_set_output(int gpio);
static int gpio_set_input(int gpio);


/* Pull the SDA gpio pin low */
static int SDA_gpio_pull_low(void) {

	int result=0;

	/* This function should set the SDA GPIO direction to out */
	/* and then write the value '0' to sda_fd		  */

	/* YOUR CODE HERE */

	/* return the result of the write() call */

	return result;

}

/* Pull the SCL gpio pin low */
static int SCL_gpio_pull_low(void) {

	int result=0;

	/* This function should set the GPIO direction to write */
	/* and then write the value '0' to sda_fd		*/

	/* YOUR CODE HERE */

	/* return the result of the write() call */

	return result;

}

/* Let SDA float high */
static int SDA_gpio_float_high(void) {

	int result=0;

	/* This function should set the SDA GPIO direction to input	*/
	/* Which allows the open collector bus to float high		*/

	/* YOUR CODE HERE */

	return result;

}

/* Let SCL float high */
static int SCL_gpio_float_high(void) {

	int result=0;

	/* This function should set the SCL GPIO direction to input	*/
	/* Which allows the open collector bus to float high		*/

	/* YOUR CODE HERE */

	return result;

}

/* read the value of SDA */
static int read_SDA(void) {

	unsigned char value=0;

	/* This function should set the GPIO direction to read	*/
	/* rewind the file descriptor, then read SDA.		*/
	/* remember to convert from ASCII before returning.	*/

	/* YOUR CODE HERE */

	return value;
}

/* read the value of SCL */
static int read_SCL(void) {

	unsigned char value=0;

	/* This function should set the GPIO direction to read	*/
	/* rewind the file descriptor, then read SCL		*/
	/* remember to convert from ASCII before returning.	*/

	/* YOUR CODE HERE */

	return value;
}



static int I2C_delay(void) {

	usleep(4);	/* 4us, although due to sysfs overhead */
			/* and inherent usleep() limitations   */
			/* we are going to be much slower.     */

	return 0;

}


static void i2c_start_bit(void) {

	/* For a start bit, SDA goes from high to low while SCL is high */

	/* YOUR CODE HERE */

	return;
}


static void i2c_stop_bit(void) {

	/* For a stop bit, SDA goes from low to high while SCL is high */

	/* YOUR CODE HERE */


}

static int i2c_read_bit(void) {

	int bit=0;

	/* Let SDA and SCL go high.  Then read SDA.  The set SCL low */

	/* YOUR CODE HERE */


	return bit;

}

static int i2c_write_bit(int bit) {

	/* Pull SCL low.  Set sda to the value you want. */
	/* Then toggle SCL high then low */

	/* YOUR CODE HERE */


	return 0;

}

	/* Write 8 bits out and check for NACK */
static int i2c_write_byte(unsigned char byte) {

	int nack=1;

	/* YOUR CODE HERE */

	return nack;
}


	/* Write a series of bytes */
int write_i2c(unsigned char *bytes, int number) {

	int i;
	int result;

	i2c_start_bit();

	for(i=0;i<number;i++) {
		result=i2c_write_byte(bytes[i]);
		if (result<0) printf("Error writing!\n");
	}

	i2c_stop_bit();

	return 0;

}




/* Set the GPIO direction to be write */
static int gpio_set_output(int gpio) {

        FILE *fff;
        char string[BUFSIZ];

        sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

        fff=fopen(string,"w");
        if (fff==NULL) {
                fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
                return -1;
        }
        fprintf(fff,"out\n");
        fclose(fff);

        return 0;
}

/* Set the gpio direction to be read */
static int gpio_set_input(int gpio) {

        FILE *fff;
        char string[BUFSIZ];

        sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

        fff=fopen(string,"w");
        if (fff==NULL) {
                fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
                return -1;
        }
        fprintf(fff,"in\n");
        fclose(fff);

        return 0;
}



/* Enable the GPIO for user use */
static int gpio_enable(int gpio) {

        FILE *fff;

	/* printf("Enabling GPIO%d for export\n",gpio); */
	fff=fopen("/sys/class/gpio/export","w");
	if (fff==NULL) {
		fprintf(stderr,"\tError enablibg GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"%d\n",gpio);
	fclose(fff);

	return 0;

}

/* Initialize two file descriptors to be used for SDA and SCL */
/* They are global variables to make the code a bit easier    */
static int init_gpios(int sda, int scl) {

        char string[BUFSIZ];

	/* Enable the GPIOs */
	if (gpio_enable(SDA_GPIO)<0) printf("Error enabling SDA\n");
	if (gpio_enable(SCL_GPIO)<0) printf("Error enabling SCL\n");

	/* Open the SDA fd */
	printf("Using GPIO%d as SDA\n",SDA_GPIO);
        sprintf(string,"/sys/class/gpio/gpio%d/value",SDA_GPIO);
        sda_fd=open(string,O_RDWR);
        if (sda_fd<0) {
                fprintf(stderr,"\tError getting value!\n");
                return -1;
        }

	/* Open the SCL fd */
	printf("Using GPIO%d as SCL\n",SCL_GPIO);
	sprintf(string,"/sys/class/gpio/gpio%d/value",SCL_GPIO);

        scl_fd=open(string,O_RDWR);
        if (scl_fd<0) {
                fprintf(stderr,"\tError getting value!\n");
                return -1;
        }

	/* Set the read/write direction of the GPIOs */
	gpio_set_input(SDA_GPIO);
	gpio_set_input(SCL_GPIO);

	return 0;

}

int main(int argc, char **argv) {

	int result;
	unsigned char buffer[17];


	/*******************************************/
	/* Init the GPIO lines we are going to use */
	/* to bitbang the i2c                      */
	/*******************************************/
	result=init_gpios(SDA_GPIO,SCL_GPIO);
	if (result<0) {
		exit(1);
	}


	/****************************************/
	/****************************************/
	/* Start the display			*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0x70<<1 | 0x0;
	/* Command 0x20 = SYSTEM SETUP  (See p30 of manual) */
	/* Action  0x01 = Turn on oscillator */
        buffer[1]= 0x20 | 0x01;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error starting display (enable oscilator)!\n");
                return -1;
        }

	/****************************************/
	/****************************************/
	/* Turn display on, no blinking		*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0xe0;
	/* Command = 0x80 Setup*/
	/* Action = Blinking off, display on */
        buffer[1]= 0x80 | 0x1;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error starting display (turning on)!\n");
                return -1;
        }



	/****************************************/
	/****************************************/
	/* Set Brightness			*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0xe0;
	/* Command = 0xe0 Dimming */
	/* Action = Brightness = 10/16 */
        buffer[1]= 0xe0 | 0xa;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error setting brightness!\n");
                return -1;
        }


	while(1) {

		/* Address of device, and we want to write */

		buffer[0]= 0xe0;

		/* Command 0x0, address = 0x0 */
		buffer[1]=0x0;

		/* Turn on all bits in display */

                buffer[2]=0xff;
                buffer[4]=0xff;
                buffer[6]=0xff;
                buffer[8]=0xff;
                buffer[10]=0xff;

		result=write_i2c(buffer,17);

		usleep(500000);


		/* Address of device, and we want to write */

		buffer[0]= 0xe0;


		/* Command 0x0, address = 0x0 */

		buffer[1]=0x0;

		/* Turn off all bits in display */

                buffer[2]=0x0;
                buffer[4]=0x0;
                buffer[6]=0x0;
                buffer[8]=0x0;
                buffer[10]=0x0;

		result=write_i2c(buffer,17);

		usleep(500000);

	}

	return 0;

}
