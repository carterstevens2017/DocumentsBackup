#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int **initarray(int columns, int row);

int main(int argc, char *argv[]){
	char *p;
	int  argcount, i;
	int columns = atoi(argv[1]);
	int rows = atoi(argv[2]);
	
	/*Checks for correct number of arguments*/
	if (argc != 3){
		printf("Enter two arguments");
		return 1;
	}
	/*Checks if arguments are negative*/	
	if ( rows  < 0 || columns < 0){
		printf("Error: Negative Number\n");
		return 1;
	}
	/*Checks if arguments are integers*/
	for( argcount=1; argcount<=argc; argcount++){
		p = argv[argcount];
		while( *p != '\0' ){
			if ( *p < '0' || *p > '9'){
				printf("Error: Enter Integers\n");
				return 1;
			}
			p++;
		}
	}
	/*Initializes array*/
	int **arr = initarray(columns, rows);
	
	/*Frees memory before exiting*/	
	for (i=0; i<columns; i++){
		free(arr[i]);
		printf("Column %d freed", i);
	}
	free(arr);
	printf("Freeing complete");

	return 0;
	
}

int **initarray(int columns, int rows){
	int **arr;
	int i;
	
	/*Allocates array of pointers for columns*/
	arr = (int **)malloc(columns * sizeof(int *));
	if (arr == NULL){
		printf("Error allocating columns");
		exit(1);
	}
	/*Allocates array of ints for each pointer of first array*/
	for (i=0; i<columns; i++){
		arr[i] = (int *)malloc(rows * sizeof(int));
		/*Frees allocated memory if allocation of rows fails*/
		if (arr[i] == NULL){
			printf("Error allocating rows");
			while (i--){
				free(arr[i]);
				printf("Row %d freed", i);
			}
			free(arr);
			printf("Free complete");
			exit(2);
		}
	}
	return arr;
}


