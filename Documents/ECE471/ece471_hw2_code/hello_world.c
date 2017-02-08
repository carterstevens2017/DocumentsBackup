#include <stdio.h>
#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"

int main(int argc, char **argv) {
	int i=1;
	
	for(i=1; i<=20; i++){
		if(i%2==0){
			printf(ANSI_COLOR_GREEN "#%d:  ECE471 I Love Pi\n",i);
		}
		else if(i%3==0){
			printf(ANSI_COLOR_CYAN "#%d:  ECE471 I Love Pi\n",i);
		}
		else{
			printf(ANSI_COLOR_RED "#%d:  ECE471 I Love Pi\n",i);
		}
	}
	return 0;
}
