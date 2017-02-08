#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int i, port, sockfd, newsockfd;
	char *prog;
	struct sockaddr_in serv_addr, cli_addr;

	if(argc == 1){
		help();
		return 0;
	}	
	for(i=0; i<argc; i++){
		if (strcmp(argv[i],"-s") == 0){
			if(argv[i+1] == NULL){
				strcpy(prog, "a.out");
			}
			else{
				strcpy(prog, argv[i+1]);
			}
		}
		else if (strcmp(argv[i],"-p") == 0){
			if(argv[i+1] == NULL){
				port = 2048;
			}
			else{
				port = argv[i+1];
			}
		}
		else{
			help();
			return 0;
		}
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("ERROR opening socket");
		return -1;
	}


}
