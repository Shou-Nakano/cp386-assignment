**Project Title:**

CP386 - Assignment 4: Bankers' Algorithm

**Motivation:**

To run the bankers' algorithm in C on a variety of processes that require a variety of resources of varying types in an easy-to-understand format. 

The program would simulate a bank machine keeping track of resources, with customers requesting and releasing resources to and from the bank. The banker will only grant a request if it leaves the system in a safe state.

**Installation:**

Copy the code in the C file into a nano file named a4.c

Copy the sample text (or your own text) into a nano file named sample4_in.txt

Save the code and type make (providing that the Makefile.mk file has been set up).

Type ./Assignment_4 sample4_in.txt to start the program.

**Screenshots:**

![Screenshot #1](https://i.imgur.com/gjAHIds.png)

![Screenshot #2](https://i.imgur.com/0fBR4g1.png)

**Individual Contribution:**

Shou Nakano:

int main(int argc, char **argv);

int ReadFile (char* fileName);

void RQ(char* command);

void RL(char* command);

void Asterisk(); 

&nbsp;
&nbsp;

Danni (Rachel) Shang:

void* threadExec(void* t);

void Run(Thread** threads);

int SafetyAlgorithm();

**Features:**

-Reads from a text file with a variable number of processes/instances of various types of resources.

-Takes input from the user in order to set up the number of resources at the start of the program.

-Allows for the user to allocate/deallocate resources from processes and runs tests to see if said allocations/deallocations are valid and leaves the system in a safe state.

-Displays a safe sequence and runs the threads in the order of the sequence with the 'Run' command.

-Contains a safety algorithm, which is used to check to see if an allocation/deallocation is valid or not.

**Tests:**

TEST #1:

osc@ubuntu:~$ ./Assignment_4 10 6 7 8

Number of Customers: 5

Currently Available Resources: 10 6 7 8

Maximum resources from file:

6,4,7,3

4,2,3,2

2,5,3,3

6,3,3,2

5,6,7,5

Input your command: 0 1 1 1 10

Invalid input; please input a valid command. 

Input your command: RQ 1 1 1 1 1

RQ Request granted.

Input your command: RQ 1 1 1 1 10

Invalid.\
Thread requested more resources than it needs.\
Resource type 3 not available.\
RQ Request denied; reversing the process with RL.\
RL Request granted.

Input your command: RL 1 1 1 1 1

RL Request granted.

Input your command: RQ 0 1 1 1 2

RQ Request granted.

Input your command: *

Currently Available Resources:

9 5 6 6

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

Current State: Safe\
Safe Sequence Is: < 0 1 2 3 4 >\
Now going to execute the threads:

---------------------------------------\
--> Customer/Thread 0 \
        Need:    5 3 6 1\
	Allocated resources:    1 1 1 2\
	Available:    9 5 6 6\
	Thread 0 has started\
	Request all needed resources\
	RQ Request granted.\
	New need array:    0 0 0 0\
	New allocation array:    6 4 7 3\
	New available array:    4 2 0 5\
	State still safe: Yes\
	Thread 0 has finished\
	Thread is releasing resources\
	RL Request granted.\
	Now available:    10 6 7 8\
---------------------------------------\
--> Customer/Thread 1 \
        Need:    4 2 3 2\
	Allocated resources:    0 0 0 0\
	Available:    10 6 7 8\
	Thread 1 has started\
	Request all needed resources\
	RQ Request granted.\
	New need array:    0 0 0 0\
	New allocation array:    4 2 3 2\
	New available array:    6 4 4 6\
	State still safe: Yes\
	Thread 1 has finished\
	Thread is releasing resources\
	RL Request granted.\
	Now available:    10 6 7 8\
---------------------------------------\
--> Customer/Thread 2 \
        Need:    2 5 3 3\
	Allocated resources:    0 0 0 0\
	Available:    10 6 7 8\
	Thread 2 has started\
	Request all needed resources\
	RQ Request granted.\
	New need array:    0 0 0 0\
	New allocation array:    2 5 3 3\
	New available array:    8 1 4 5\
	State still safe: Yes\
	Thread 2 has finished\
	Thread is releasing resources\
	RL Request granted.\
	Now available:    10 6 7 8\
---------------------------------------\
--> Customer/Thread 3 \
        Need:    6 3 3 2\
	Allocated resources:    0 0 0 0\
	Available:    10 6 7 8\
	Thread 3 has started\
	Request all needed resources\
	RQ Request granted.\
	New need array:    0 0 0 0\
	New allocation array:    6 3 3 2\
	New available array:    4 3 4 6\
	State still safe: Yes\
	Thread 3 has finished\
	Thread is releasing resources\
	RL Request granted.\
	Now available:    10 6 7 8\
---------------------------------------\
--> Customer/Thread 4 \
        Need:    5 6 7 5\
	Allocated resources:    0 0 0 0\
	Available:    10 6 7 8\
	Thread 4 has started\
	Request all needed resources\
	RQ Request granted.\
	New need array:    0 0 0 0\
	New allocation array:    5 6 7 5\
	New available array:    5 0 0 3\
	State still safe: Yes\
	Thread 4 has finished\
	Thread is releasing resources\
	RL Request granted.\
	Now available:    10 6 7 8
	
&nbsp;
&nbsp;

TEST #2:

osc@ubuntu:~$ ./Assignment_4 10 5 7 8

Number of Customers: 5

Currently Available Resources: 10 5 7 8

Maximum resources from file:

6,4,7,3

4,2,3,2

2,5,3,3

6,3,3,2

5,6,7,5

Input your command: Run

Current State: Not safe\
Currently not in safe state; please enter a different set of resources. 

**Code Example:**

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

&nbsp;
&nbsp;

Example of struct Thread: 

```
typedef struct thread // Represents a single thread
{
	int index; // Thread number
	int order; // Safe sequence order of threads
	pthread_t handle;
	int retVal; // Return value
} Thread;
```

**Authors:**

Shou Nakano

Danni (Rachel) Shang

**Credits:**

Examples of strtok(), atoi(), fgets(), malloc() and other functions were used in order to properly create multiple functions.

**License:**

MIT License

Copyright (c) 2020, Shou Nakano/Danni (Rachel) Shang

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
