Project Title:
CP386: Assignment 4: Bankers' Algorithm
Motivation:
To run the bankers' algorithm in C on a variety of processes that require a variety of resources of varying types in an easy-to-understand format.
Installation:
Copy the code in the C file into nano a4.c
Type
Screenshots:

Individual Contribution:
Shou Nakano:
int main(int argc, char **argv);
int ReadFile (char* fileName);
void RQ(char* command);
void RL(char* command);
void Asterisk();

Rachel Danni Shang:
void Run();
int SafetyAlgorithm();

Features:

Tests:

Code Example:
Example of Asterisk():
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

Authors:
Shou Nakano
Rachel Danni Shang

Credits:

License:

