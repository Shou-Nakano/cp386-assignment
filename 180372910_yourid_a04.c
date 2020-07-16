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


	readFile(argv[1]);
	
}

int readFile(char* fileName) // Reads the input file and sets up the vectors/matrices.
{
	// How many lines are in the file?
	FILE *in = fopen(fileName, "r");

	if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}

}

void RQ(){

}

void RL(){

	safetyAlgorithm();

}

void asterisk(){
	
}

void run(){ // This function should use safetyAlgorithm to check to see if there is a safe series of threads and if so, 'run' them as seen in the sample output.
	
}

int safetyAlgorithm(){ // This function should contain the safety algorithm that will be called by RQ, RL and run and will update the vector containing the safe sequence. If there is a safe sequence, return 1, if not, return 0. This should also update a vector containing the safe sequence.
 	
}