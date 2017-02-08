#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() 
{

	pid_t pid;				

	pid = fork();				//splits process
	if (pid < 0){				//fork returns -1 on fail
		perror("Failed to fork");
		return -1;
	}

	if ( pid == 0 ){			//child process has id of 0
		while(1){
			sleep(1);
		}
	} 
	else {					//parent process has positive id
		kill(pid, SIGKILL);		//kills process signal
		sleep(10);
	}
	return 0;
}
