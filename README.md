Project Title:
CP386: Assignment 4: Bankers' Algorithm

Motivation:
To run the bankers' algorithm in C on a variety of processes that require a variety of resources of varying types in an easy-to-understand format.

Installation:
Copy the code in the C file into a nano file named a4.c
Copy the sample text (or your own text) into a nano file named sample4_in.txt
Save the code and type make (providing that the Makefile.mk file has been set up).
Type ./Assignment_4 sample4_in.txt to start the program.

Screenshots:

![Screenshot #1](https://i.imgur.com/gjAHIds.png)
![Screenshot #2](https://i.imgur.com/0fBR4g1.png)

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
-Reads from a text file with a variable number of processes/types of resources.
-Takes input from the user in order to set up the number of resources at the start of the program.
-Allows for the user to allocate/deallocate resources from processes and runs tests to see if said allocations/deallocations are valid.
-Runs the threads in the text file with the 'Run' command.
-Contains a safety algorithm, which is used to check to see if an allocation/deallocation is valid or not.

Tests:

osc@ubuntu:~$ ./Assignment_4 4 4 4 4
Number of Customers: 5
Currently Available Resources: 4 4 4 4
Maximum resources from file:
6,4,7,3
4,2,3,2
2,5,3,3
6,3,3,2
5,6,7,5
Input your command: RQ 0 1 1 1 1
RQ Request granted.
Input your command: RL 0 1 1 1 10
RL Request denied; reverseing the process with RQ.
RQ Request granted.
Input your command: RL 0 1 1 1 1
RL Request granted.
Input your command: RQ 0 1 1 1 2
RQ Request granted.
Input your command: *
Currently Available Resources:
3 3 3 2
Maximum Allocatable Resources (each row is a process):
6 4 7 3
4 2 3 2
2 5 3 3
6 3 3 2
5 6 7 5

Currently Allocated Resources (each row is a process):
1 1 1 2
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

Currently Needed Resources (each row is a process):
5 3 6 1
4 2 3 2
2 5 3 3
6 3 3 2
5 6 7 5

Input your Command: Run

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
Example of strtok(), atoi(), fgets(), malloc() and other functions were used in order to properly create multiple functions.

License:

MIT License

Copyright (c) 2020, Shou Nakano/Rachel Danni Shang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.