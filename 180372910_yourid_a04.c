#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	
	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}


	readFile();
	
}

void readFile(){

}