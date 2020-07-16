#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadFile (char* fileName);
void RQ(char* command);
void RL(char* command);
void Asterisk();
void Run();
int SafetyAlgorithm();

int done = 0;
int *available = NULL; // 1D vector for resources, which stores the number of available resources of each type. If available [j] = k, there are k instances of resource type Rj available.
int ** max = NULL; // 2D array (number of processes by number of resources). If Max [i,j] = k, then process Ti may request at most k instances of resource type Rj.
int ** allocation = NULL; // 2D array (number of processes by number of resources). If Allocation[i,j] = k then Ti is currently allocated k instances of Rj.
int ** need = NULL; // 2D array (number of processes by number of resources). If Need[i,j] = k, then Ti will need k more instances of Rj to complete its task.
int varArgc;
char ** varArgv = NULL;



// The vectors/matrices will be defined here as global variables.

int main(int argc, char **argv) {
	char *prelude = (char*)malloc(100); // This will be used to get rid of the tokens in the fgets string.
	char *command = (char*)malloc(100);
	if(argc<2)
	{
		printf("No initial resources provided, exiting with error code -1. \n");
		return -1;
	}
	// printf("%d", atoi(argv[1]) * 2); This is a test and this works.
	varArgc = argc;
	varArgv = argv;
	ReadFile("sample4_in.txt");
	// Prompt the user for input here. We should assume that using the run command ends the program.
	while (done == 0){
		printf("Input your command: ");
		fgets(command, 100, stdin); // We must use fgets to get the user's input, since their input will have spaces.
		// Run a function based on the user's input.
		if (strncmp(command, "RQ", 2) == 0){
			RQ(command);
		}
		else if (strncmp(command, "RL", 2) == 0){
			RL(command);
		}
		else if (strncmp(command, "*", 1) == 0){
			Asterisk();
		}
		else if (strncmp(command, "Run", 3) == 0){
			done = 1;
			Run();
		}
		else{
			printf("Invalid input; please input a valid command.");
		}
		while(prelude != NULL) {
			prelude = strtok(NULL, " ");
		}
	}
	free(available); // Don't forget to free everything at the end of the program.
	free(max);
	free(allocation);
	free(need);
	return 0;
}

int ReadFile(char* fileName) // Reads the input file and sets up the vectors/matrices. Presumably complete.
{
	FILE *in = fopen(fileName, "r");
	char filePointer;
	int lines;
	int commas;
	int resources; // Resources should equal (commas+lines)/lines.
	int processes;

	if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}
	// How many lines/commas and by extension, resources are in the file?
	filePointer = fgetc(in);
	while (filePointer != EOF)
    {
        if (filePointer == '\n'){
            lines = lines + 1; // Increment the line count.
        }
		if (filePointer == ','){
			commas = commas + 1; // Increment the comma count.
		}
        //Move to the next character.
        filePointer = fgetc(in);
    }
	processes = lines;
	resources = (commas+lines)/lines; // This works, for sample4_in.txt, it printed 4.
	// Next, dynamically set up the vectors/matrices.
	available = (int *)malloc(resources * sizeof(int)); // Create the Available vector.
	max = (int **)malloc(processes * sizeof(int *));
	for (int i=0; i<processes; i++){
         max[i] = (int *)malloc(resources * sizeof(int)); // Create the max matrix.
	}
	allocation = (int **)malloc(processes * sizeof(int *));
	for (int i=0; i<processes; i++){
         allocation[i] = (int *)malloc(resources * sizeof(int)); // Create the allocation matrix.
	}
	need = (int **)malloc(processes * sizeof(int *));
	for (int i=0; i<processes; i++){
         need[i] = (int *)malloc(resources * sizeof(int)); // Create the need matrix.
	}
	// Finally, fill the contents of those vectors/matrices.
	// Set up available from argv.
	for (int i=1; i < (varArgc); i++){
		available[i] = atoi(*(varArgv+i));
	}
	fseek(in, 0, SEEK_SET);
	// Set up max/need (which are the same to start).
	int i = 0;
	int j = 0;
	char *temp;
	filePointer = fgetc(in);
	while (filePointer != EOF){
		if (filePointer != '\n' && filePointer != ','){
			temp = &filePointer;
			max[i][j] = atoi(temp);
			need[i][j] = atoi(temp);
			j = j + 1;
			if (j == resources){
				j = 0;
				i = i + 1;
			}
		}
		filePointer = fgetc(in);
	}
	// Set up allocation (every elemene in allocation is 0).
	i = 0;
	j = 0;
	for (i = 0; i < processes; i++){
		for (j = 0; j < resources; j++){
			allocation[i][j] = 0;
		}
	}
	return 0;
}

void RQ(char* command){
	char* save = (char*) malloc(100);
	strcpy(save, command); // Just in case we shouldn't RQ, we can use this same command to perform a RL.
	save[1] = 'L';
	printf("%s", save);
	char *token = strtok(command, " "); // Get rid of the RQ bit in the command.
	int i = atoi(strtok(NULL, " ")); // Which row of the matrix should we look at?
	int j = 0;
	int number; // What is the token as a number?
	int valid = 0; // Is this request valid? 0 if it is, -1 if it isn't. This will be checked by making sure that we don't exceed the maximum requestable resources for a thread.
	int safe = 0; // Is this request safe? 0 if it is, -1 if it isn't.
	token = strtok(NULL, " ");
	while (token != NULL){
		number = atoi(token);
		allocation[i][j] = allocation[i][j] + number;
		need[i][j] = need[i][j] - number;
		if (need[i][j] < 0){ // This means that the thread has requestable more resources than it needs...
			valid = -1;
		}
		j++;
		token = strtok(NULL, " ");
	}
	safe = SafetyAlgorithm();
	if (valid == -1 || safe == -1){
		RL(save);
	}
}

void RL(char* command){
	printf("RL has run with the command %s.", command);
}

void Asterisk(){
	
}

void Run(){ // This function should use safetyAlgorithm to check to see if there is a safe series of threads and if so, 'run' them as seen in the sample output.
	printf("Run");
}

int SafetyAlgorithm(){ // This function should contain the safety algorithm that will be called by RQ, RL and run and will update the vector containing the safe sequence. If there is a safe sequence, return 0, if not, return -1. This should also update a vector containing the safe sequence.
 	return 0;
}