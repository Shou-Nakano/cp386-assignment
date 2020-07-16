#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readFile (char* fileName);
void RQ();
void RL();
void asterisk();
void run();
int safetyAlgorithm();

public int done = false;

// The vectors/matrices will be defined here as global variables.

int main(int argc, char *argv[]) {
	
	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

	readFile(argv[1]);
	// Prompt the user for input here. We should assume that using the run command ends the program.
	while (done == false){
		
	}

	free(available); // Don't forget to free everything at the end of the program.
	return 0;
}

int readFile(char* fileName) // Reads the input file and sets up the vectors/matrices.
{
	FILE *in = fopen(fileName, "r");
	char filePointer;
	int lines;
	int commas;
	int resources; // Resources should equal (commas+lines)/lines.
	int *available = null; // 1D array for resources.

	if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}
	// How many lines/commas and by extension, resources are in the file?
	filePointer = getc(in);
	while (filePointer != EOF)
    {
        if (filePointer == '\n'){
            lines = lines + 1; // Increment the line count.
        }
		if (filePointer == ','){
			commas = commas + 1; // Increment the comma count.
		}
        //Move to the next character.
        filePointer = getc(in);
    }

	resources = (commas+lines)/lines; // This works, for sample4_in.txt, it printed 4.
	// Next, dynamically set up the vectors/matrices.
	available = (int *)malloc(resources * sizeof(int)); // Create the Available vector.
	// Finally, fill the contents of those vectors/matrices.

	return 0;
}

void RQ(){

}

void RL(){

	safetyAlgorithm();

}

void asterisk(){
	
}

void run(){ // This function should use safetyAlgorithm to check to see if there is a safe series of threads and if so, 'run' them as seen in the sample output.
	done = true;
}

int safetyAlgorithm(){ // This function should contain the safety algorithm that will be called by RQ, RL and run and will update the vector containing the safe sequence. If there is a safe sequence, return 0, if not, return -1. This should also update a vector containing the safe sequence.
 	return 0;
}