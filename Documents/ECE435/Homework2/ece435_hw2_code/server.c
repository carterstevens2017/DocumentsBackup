#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE	256

/* Default port to listen on */
#define DEFAULT_PORT	31337

int main(int argc, char **argv) {

	int socket_fd,new_socket_fd;
	struct sockaddr_in server_addr, client_addr;
	int port=DEFAULT_PORT;
	int n=1;
	int i=0;
	socklen_t client_len;
	char buffer[BUFFER_SIZE];

	printf("Starting server on port %d\n",port);

	/* Open a socket to listen on */
	/* AF_INET means an IPv4 connection */
	/* SOCK_STREAM means reliable two-way connection (TCP) */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd<0) {
		fprintf(stderr,"Error opening socket! %s\n",
			strerror(errno));
	}

	/* Set up the server address to listen on */
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	/* Convert the port we want to network byte order */
	server_addr.sin_port=htons(port);

	/* Bind to the port */
	if (bind(socket_fd, (struct sockaddr *) &server_addr,
		sizeof(server_addr)) <0) {
		fprintf(stderr,"Error binding! %s\n", strerror(errno));
	}

	/* Tell the server we want to listen on the port */
	/* Second argument is backlog, how many pending connections can */
	/* build up */
	listen(socket_fd,5);

	/* Call accept to create a new file descriptor for an incoming */
	/* connection.  It takes the oldest one off the queue */
	/* We're blocking so it waits here until a connection happens */
	client_len=sizeof(client_addr);
	new_socket_fd = accept(socket_fd,
		(struct sockaddr *)&client_addr,&client_len);
	if (new_socket_fd<0) {
		fprintf(stderr,"Error accepting! %s\n",strerror(errno));
	}
	/* Once connection has been made, loop */
	while(1){
		/* Someone connected!  Let's try to read BUFFER_SIZE-1 bytes */
		memset(buffer,0,BUFFER_SIZE);
		n = read(new_socket_fd,buffer,(BUFFER_SIZE-1));
		if (n==0) {
			fprintf(stderr,"Connection to client lost\n\n");
			break;
		}
		else if (n<0) {
			fprintf(stderr,"Error reading from socket %s\n",
			strerror(errno));
			break;
		}
		/* Checks to see if the read string says "bye" and exits if so*/	
		if (!(strncmp(buffer , "bye",3)) != 0){
			n = write(new_socket_fd,"Goodbye my friend",17);
			close(new_socket_fd);
			close(socket_fd);
			break;
		}
		/*Changes all characters in the buffer to their uppercase equivalent*/
		for(i=0; i<BUFFER_SIZE; i++){
			buffer[i] = toupper(buffer[i]);
		}

		/* Print the message we received */
		printf("Message from client: %s\n",buffer);

		

		/* Send a response */
		n = write(new_socket_fd, buffer, 25);
		if (n<0) {
			fprintf(stderr,"Error writing. %s\n",
				strerror(errno));
		}
	}

	printf("Exiting server\n\n");

	/* Try to avoid TIME_WAIT */
//	sleep(1);

	/* Close the sockets */
	close(new_socket_fd);
	close(socket_fd);

	return 0;
}
