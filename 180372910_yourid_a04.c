#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
// Define the values of booleans false and true
#define FALSE 0
#define TRUE 1
#define SIZE 100

typedef struct thread // Represents a single thread
{
	int index; // Thread number
	int order; // Safe sequence order of threads
	pthread_t handle;
	int retVal; // Return value
} Thread;

int ReadFile (char* fileName);
void RQ(char* command);
void RL(char* command);
void Asterisk();
void Run(Thread** threads);
int SafetyAlgorithm();
void* threadExec(void* t);

int done = 0;
int *available = NULL; // 1D vector for resources, which stores the number of available resources of each type. If available [j] = k, there are k instances of resource type Rj available.
int ** max = NULL; // 2D array (number of processes by number of resources). If Max [i,j] = k, then process Ti may request at most k instances of resource type Rj.
int ** allocation = NULL; // 2D array (number of processes by number of resources). If Allocation[i,j] = k then Ti is currently allocated k instances of Rj.
int ** need = NULL; // 2D array (number of processes by number of resources). If Need[i,j] = k, then Ti will need k more instances of Rj to complete its task.
int varArgc;
char ** varArgv = NULL;
int *safeSeq = NULL; // 1D vector to store safe sequence
int *work = NULL; // 1D vector for SafetyAlgorithm(); stores current available resource instances
int *finish = NULL; // 1D vector for SafetyAlgorithm(); stores which processes have finished execution
Thread* threads = NULL; // Thread object to store all threads
sem_t semaphore; // Declare a semaphore
int ret // Return value for semaphore
int *tempSeq = NULL; // 1D vector to store temporary safe sequence for run()

int rows; // Number of rows in the matrix (# of threads/processes).
int columns; // Number of columns in the matrix (# of instances per resource).


// The vectors/matrices will be defined here as global variables.

int main(int argc, char **argv) {
	
	// Initiate threads object so that it's big enough to store all threads
	threads = (Thread*) malloc(sizeof(Thread)*rows); 
	
	char *prelude = (char*)malloc(SIZE); // This will be used to get rid of the tokens in the fgets string.
	char *command = (char*)malloc(SIZE);
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
		fgets(command, SIZE, stdin); // We must use fgets to get the user's input, since their input will have spaces.
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
			Run(&threads);
		}
		else{
			printf("Invalid input; please input a valid command. \n");
		}
		while(prelude != NULL) {
			prelude = strtok(NULL, " ");
		}
	}
	// Frees all resources at end of the program
	free(available); 
	free(max);
	free(allocation);
	free(need);
	free(safeSeq);
	free(tempSeq);
	return 0;
}

int ReadFile(char* fileName) // Reads the input file and sets up the vectors/matrices. Presumably complete.
{
	int processes;
	int resources; // Resources should equal (commas+lines)/lines.
	FILE *in = fopen(fileName, "r");
	char filePointer;
	int lines;
	int commas;

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
	rows = processes;
	columns = resources;
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
		available[i-1] = atoi(*(varArgv+i));
	}
	fseek(in, 0, SEEK_SET);
	// Set up max/need (which are the same to start).
	int i = 0;
	int j = 0;
	char *temp;
	filePointer = fgetc(in);
	// Print some basic information.
	printf("Number of Customers: %d", processes);
	printf("\n");
	printf("Currently Available Resources: ");
	for (j = 0; j < resources; j++){
		printf("%d ", available[j]);
	}
	i = 0;
	j = 0; // Reset i and j.
	printf("\n");
	printf("Maximum resources from file: \n");
	while (filePointer != EOF){
		printf("%c", filePointer);
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
	// Set up allocation (every element in allocation starts as 0).
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
	char* save = (char*) malloc(SIZE);
	strcpy(save, command); // Just in case we shouldn't RQ, we can use this same command to perform a RL.
	save[1] = 'L';
	char *token = strtok(command, " "); // Get rid of the RQ bit in the command.
	int i = atoi(strtok(NULL, " ")); // Which row of the matrix should we look at?
	int j = 0;
	int number; // What is the token as a number?
	int valid = 0; // Is this request valid? 0 if it is, -1 if it isn't. This will be checked by making sure that we don't exceed the maximum requestable resources for a thread.
	int safe = 0; // Is this request safe? 0 if it is, -1 if it isn't.
	// Gives more information on why input is invalid
	int error1 = 0;
	int error2 = -1;
	token = strtok(NULL, " ");
	while (token != NULL){
		number = atoi(token);
		available[j] = available[j] - number;
		allocation[i][j] = allocation[i][j] + number;
		need[i][j] = need[i][j] - number;
		if (need[i][j] < 0){ // This means that the thread has requested more resources than it needs.
			valid = -1;
			error1 = -1;
		}
		if (available[j] < 0){ // This means that you don't have enough resources to give to the thread.
			valid = -1;
			error2 = j;
		}
		j++;
		token = strtok(NULL, " ");
	}
	safe = SafetyAlgorithm();
	if (valid == -1 || safe == -1){
		if (valid == -1) {
			printf("Invalid.\n");
		}
		if (error1 == -1) {
			printf("         Thread requested more resources than it needs.\n");
		}
		if (error2 != -1) {
			printf("         Not enough resources available.\n");
		}
		if (safe == -1) {
			printf("Unsafe state.\n");
		}
		printf("RQ Request denied; reversing the process with RL. \n");
		// If request denied, release allocated resources to reverse process and return to previous state
		RL(save);
	}
	else{
		printf("RQ Request granted. \n");
	}
}

void RL(char* command){
	char* save = (char*) malloc(SIZE);
	strcpy(save, command); // Just in case we shouldn't RL, we can use this same command to perform a RQ.
	save[1] = 'Q';
	char *token = strtok(command, " "); // Get rid of the RL bit in the command.
	int i = atoi(strtok(NULL, " ")); // Which row of the matrix should we look at?
	int j = 0;
	int number; // What is the token as a number?
	int valid = 0; // Is this request valid? 0 if it is, -1 if it isn't. This will be checked by making sure that we don't give a thread less than 0 resources.
	token = strtok(NULL, " ");
	while (token != NULL){
		number = atoi(token);
		available[j] = available[j] + number;
		allocation[i][j] = allocation[i][j] - number;
		need[i][j] = need[i][j] + number;
		if (allocation[i][j] < 0){ // This means that the thread has more resources than it needs...
			valid = -1;
		}
		j++;
		token = strtok(NULL, " ");
	}
	if (valid == -1){
		printf("RL Request denied; reversing the process with RQ. \n");
		RQ(save);
	}
	else{
		printf("RL Request granted. \n");
	}
}

void Asterisk(){
	int i; // Placeholder iterator variables.
	int j;
	printf("Currently Available Resources: ");
	printf("\n");
	for (j = 0; j < columns; j++){
		printf("%d ", available[j]);
	}
	printf("\n");
	printf("Maximum Allocatable Resources (each row is a process): ");
	printf("\n");
	for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			printf("%d ", max[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Currently Allocated Resources (each row is a process): ");
	printf("\n");
	for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Currently Needed Resources (each row is a process): ");
	printf("\n");
	for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void* threadExec(void* t) { // Function invoked by a new thread created by pthread_create()

	// Decrement (lock) the semaphore
	// If the semaphore's value is greater than 0, then the decrement proceeds and function returns
	// Else the call blocks until it's possible to perform the decrement
	sem_wait(&semaphore);

	// Critical section starts here
	// Create arrays to store matrix values
	char* charArray = (char*) malloc(SIZE);
	int* intArray = (int*) malloc(SIZE);
	int number;
	
	// Put each element in Thread i's row of the need matrix into intArray
	for (int i = 0; i < columns; i++) {
		int number = need[((Thread*)t)->index][i];
		intArray[i] = number;
	}

	// Initialize charArray so that it contains 'RQ' and the thread index
	charArray[0] = 'R';
	charArray[1] = 'Q';
	charArray[2] = ' ';
	charArray[3] = ((Thread*)t)->index + '0';
	charArray[4] = ' ';

	// Put the need resources from intArray in charArray
	int j = 0;
	for (int i = 5; i < 12; i = i + 2) {
		charArray[i] = intArray[j] + '0';
		charArray[i + 1] = ' ';
		j++;
	}

	printf("        Thread %i has started\n", ((Thread*)t)->index);

	// Request needed number of resources using charArray
	printf("        Request all needed resources\n");
	printf("        ");
	RQ(charArray);

	// After the request is granted, find the new need matrix, allocation matrix, and available matrix for the given thread
	printf("        New need array:   ");
	for (int j = 0; j < columns; j++) {
		printf(" %i", need[((Thread*)t)->index][j]);
	}
	printf("\n");
	printf("        New allocation array:   ");
	for (int j = 0; j < columns; j++) {
		printf(" %i", allocation[((Thread*)t)->index][j]);
	}
	printf("\n");
	printf("        New available array:   ");
	for (int j = 0; j < columns; j++) {
		printf(" %i", available[j]);
	}
	printf("\n");

	// Check that the state remains safe after all needed resources are granted
	printf("        State still safe: ");
	int safe = SafetyAlgorithm();
	if (safe == 0) {
		printf(" Yes\n");
	}
	else {
		printf(" No\n");
	}

	printf("        Thread %i has finished\n", ((Thread*)t)->index);

	// After thread finishes execution, create another char array and int array to store values of allocated resources
	char* charArrayRL = (char*) malloc(SIZE);
	int* intArray2 = (int*) malloc(SIZE);
	for (int i = 0; i < columns; i++) {
		number = allocation[((Thread*)t)->index][i];
		intArray2[i] = number;
	}

	// Initiate charArrayRL so that it contains 'RL' and the thread index
	charArrayRL[0] = 'R';
	charArrayRL[1] = 'L';
	charArrayRL[2] = ' ';
	charArrayRL[3] = ((Thread*)t)->index + '0';
	charArrayRL[4] = ' ';

	// Put the allocated resources from intArray2 to charArrayRL
	j = 0;
	for (int i = 5; i < 12; i = i + 2) {
		charArrayRL[i] = intArray2[j] + '0';
		charArrayRL[i + 1] = ' ';
		j++;
	}

	// Release all allocated resources for the given thread
	printf("        Thread is releasing resources\n");
	printf("        ");

	RL(charArrayRL);

	// Display the new available matrix (all resource instances should now be available)
	printf("        Now available:");
	for (int i = 0; i < columns; i++) {
		printf(" %i", available[i]);
	}
	printf("\n");

	// Critical section ends here

	// Increment (unlock) the semaphore so that the next thread can access it
	sem_post(&semaphore);

	// Upon completion, terminate the thread
	pthread_exit(0);
	return 0;

}

void Run(Thread** threads){ // This function should use safetyAlgorithm to check to see if there is a safe series of threads and if so, 'run' them as seen in the sample output.

	// Initiate the semaphore (semaphore is shared between process threads and has an initial value of 1)
	ret = sem_init(&semaphore, 0, 1);

	// Call the safety algorithm to see whether system is in safe state
	int safe = SafetyAlgorithm();
	printf("\n");
	// Print the state of the system
	printf("Current State:");
	if (safe == -1) {
		printf(" Not safe\n");
	}
	else if (safe == 0) {
		printf(" Safe\n");
	}
	if (safe == -1){
		printf("Currently not in safe state; please enter a different set of resources.\n");
	}
	else {
		// Print the safe sequence of threads
		printf("Safe Sequence is: < ");
		for (int i = 0; i < rows; i++) {
			printf("%i ", safeSeq[i]);
			(*threads)[i].index = safeSeq[i];
			(*threads)[i].order = i;
		}
		printf(">\n");

		// Create a temporary matrix to store the current safe sequence in
		tempSeq = (int *)malloc(rows * sizeof(int));
		tempSeq = safeSeq;
		
		printf("Now going to execute the threads:\n");
		printf("\n");

		// Execute each thread in the order of the safe sequence
		for (int i = 0; i < rows; i++) {
			printf("----------------------------------------\n");
			printf("--> Customer/Thread %i\n", tempSeq[i]);
			// How many resources the thread currently needs
			printf("        Need:   ");
			for (int j = 0; j < columns; j++) {
				printf(" %i", need[tempSeq[i]][j]);
			}
			printf("\n");
			// How many resources have been allocated to the thread
			printf("        Allocated resources:   ");
			for (int j = 0; j < columns; j++) {
				printf(" %i", allocation[tempSeq[i]][j]);
			}
			printf("\n");
			// How many instances of each resource are currently available in the system
			printf("        Available:   ");
			for (int j = 0; j < columns; j++) {
				printf(" %i", available[j]);
			}
			printf("\n");

			// Create the thread and invoke function threadExec()
			// Pass the thread as a argument to threadExec()
			(*threads)[i].retVal = pthread_create(&((*threads)[i].handle),NULL,threadExec,&((*threads)[i]));
			// execute thread
			sleep(1);
		}

		// After all threads have executed, destroy the semaphore
		sem_destroy(&semaphore);
	}
}

int SafetyAlgorithm(){ // This function should contain the safety algorithm that will be called by RQ and run and will update the vector containing the safe sequence (you'll need to create a dynamic array somewhere, like with allocation). If there is a safe sequence, return 0, if not, return -1. This should also update a vector containing the safe sequence.
 	
	// Create an array to store the safety sequence
	// Initialize as "-1" for each thread to show that sequence is currently invalid
	safeSeq = (int *)malloc(rows * sizeof(int));
	for (int i = 0; i < rows; i++) {
		safeSeq[i] = -1;
	}

	// Create vectors for Work and Finish and initialize values
	work = (int *)malloc(columns * sizeof(int));
	for (int i = 0; i < columns; i++) {
		// Initially, the work array is the same as the available array
		work[i] = available[i];
	}

	finish = (int *)malloc(rows * sizeof(int));
	// Initially, each element in the finish array is set to false because no processes have completed execution yet
	for (int i = 0; i < rows; i++) {
		finish[i] = FALSE;
	}

	// Safe variable will be returned by the function to determine if a resource request will leave the system in a safe state
	// 0 = safe, -1 = not safe
	int safe = 0;
	// Start at index 0 of the safety sequence; increment to add next element to the safety sequence array
	int sequenceNum = 0;
	// Keeps track of whether all resources meet the safe state conditions for a given process (need <= work)
	int columnCount = 0;
	// Is 1 if a process is found that meets safe state conditions (need <= work and finish[i] = false); 0 if no process found
	int found = 1;

	// Keep looping while there exists a process that meets conditions for maintaining safe state (need <= work and finish[i] = false)
	while (found == 1 && safe == 0) {
		// Set found to 0 to indicate that no process has been found yet that meets safe state conditions
		found = 0;
		// Loop through each process
		for (int i = 0; i < rows; i++) {
			// Check if the 2 conditions are met (finish[i] = false and need <= work)
			if (finish[i] == FALSE) {
				columnCount = 0;
				// Loop through all elements of the work array
				for (int j = 0; j < columns; j++) {
					// Values can't be negative
					if (need[i][j] < 0 || work[j] < 0) {
						safe = -1;
						break;
					}
					// Check to see if the resources that a process still needs are less than the available
					// number of resources found in the work array
					if (need[i][j] <= work[j]) {
						// If so, then the condition is fulfilled, so increment columnCount
						columnCount++;
					}
					else {
						// Otherwise, condition is not fulfilled, so the loop can be exited
						break;
					}
				}
				// If columnCount equals number of resources, that means that the condition need <= work is fulfilled
				if (columnCount == columns) {
					// Put the process index into the safety sequence as the next process to run
					safeSeq[sequenceNum] = i;
					// Increment the index so we can get the next process
					sequenceNum++;
					// Set finish[i] = true to show that the process has been executed
					finish[i] = true;
					// Allocated resources have been used, so increment work by the number of allocated resources
					for (int k = 0; k < columns; k++) {
						work[k] = work[k] + allocation[i][k];
					}
					// Set to 1 to show that a process that meets conditions has been found
					found = 1;
				}
			}
		}

	}

	// Print out the safety sequence
	// printf("Safety Sequence: ");
	
	for (int i = 0; i < rows; i++) {

		//printf("%i ", safeSeq[i]);

		// If all processes could finish execution (all processes are in safe sequence), then the system is in safe state
		// if finish[i] = false, then there exists a process that couldn't finish execution while maintaining safe state
		// Set safe = -1
		if (finish[i] == FALSE) {
			safe = -1;
		}
	}
	//printf("\n");

	return safe;
}
