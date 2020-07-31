The Github Repository can be found at: https://github.com/Shou-Nakano/cp386-assignment

**Project Title:**

CP386 Assignment 4: Bankers' Algorithm

**Description:**

The program would simulate a bank machine keeping track of resources, with customers requesting and releasing resources to and from the bank. The banker will only grant a request if it leaves the system in a safe state, as determined by the safety algorithm.

**Motivation:**

To run the bankers' algorithm in C on a variety of processes that require a variety of resources of varying types in an easy-to-understand format. 

**Installation:**

Copy the code in the C file into a nano file named a4.c

Copy the sample text (or your own text) into a nano file named sample4_in.txt

Save the code and type make (providing that the Makefile.mk file has been set up).

Type ./Assignment_4 [your processes here] to start the program.

**Screenshots:**

TEST #1:

![image](https://user-images.githubusercontent.com/33897109/89019333-21891180-d2eb-11ea-8443-1ece69fbd46e.png)

![image](https://user-images.githubusercontent.com/33897109/88879975-95e38800-d1f9-11ea-8975-3b1c09304a1d.png)

![image](https://user-images.githubusercontent.com/33897109/88880046-c9bead80-d1f9-11ea-9aa5-148be26d8d95.png)

![image](https://user-images.githubusercontent.com/33897109/88880094-e22ec800-d1f9-11ea-9de5-437201f944cc.png)

![image](https://user-images.githubusercontent.com/33897109/88880127-f672c500-d1f9-11ea-81e1-de25a57a49dc.png)

TEST #2:

![image](https://user-images.githubusercontent.com/33897109/88880189-17d3b100-d1fa-11ea-81a2-7817db286da1.png)

**Individual Contribution:**

Shou Nakano:

int main(int argc, char **argv);

int ReadFile (char* fileName);

void RQ(char* command);

void RL(char* command);

void Asterisk(); 

&nbsp;

Danni (Rachel) Shang:

void* threadExec(void* t);

void Run(Thread** threads);

int SafetyAlgorithm();

&nbsp;

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

Invalid:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Thread requested more resources than it needs.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Not enough resources available.\
Unsafe state.\
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

--------------------------------------------\
--> Customer/Thread 0 \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        Need:&nbsp; &nbsp; &nbsp;    5 3 6 1\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Allocated resources:&nbsp; &nbsp; &nbsp;    1 1 1 2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Available:&nbsp; &nbsp; &nbsp;    9 5 6 6\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 0 has started\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Request all needed resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RQ Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New need array:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New allocation array:&nbsp; &nbsp; &nbsp;    6 4 7 3\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New available array:&nbsp; &nbsp; &nbsp;    4 2 0 5\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	State still safe: Yes\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 0 has finished\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread is releasing resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RL Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Now available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
--------------------------------------------\
--> Customer/Thread 1 \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        Need:&nbsp; &nbsp; &nbsp;    4 2 3 2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Allocated resources:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 1 has started\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Request all needed resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RQ Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New need array:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New allocation array:&nbsp; &nbsp; &nbsp;    4 2 3 2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New available array:&nbsp; &nbsp; &nbsp;    6 4 4 6\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	State still safe: Yes\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 1 has finished\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread is releasing resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RL Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Now available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
--------------------------------------------\
--> Customer/Thread 2 \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        Need:&nbsp; &nbsp; &nbsp;    2 5 3 3\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Allocated resources:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 2 has started\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Request all needed resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RQ Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New need array:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New allocation array:&nbsp; &nbsp; &nbsp;    2 5 3 3\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New available array:&nbsp; &nbsp; &nbsp;    8 1 4 5\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	State still safe: Yes\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 2 has finished\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread is releasing resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RL Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Now available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
--------------------------------------------\
--> Customer/Thread 3 \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        Need:&nbsp; &nbsp; &nbsp;    6 3 3 2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Allocated resources:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 3 has started\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Request all needed resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RQ Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New need array:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New allocation array:&nbsp; &nbsp; &nbsp;    6 3 3 2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New available array:&nbsp; &nbsp; &nbsp;    4 3 4 6\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	State still safe: Yes\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 3 has finished\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread is releasing resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RL Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Now available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
--------------------------------------------\
--> Customer/Thread 4 \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        Need:&nbsp; &nbsp; &nbsp;    5 6 7 5\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Allocated resources:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Available:&nbsp; &nbsp; &nbsp;    10 6 7 8\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 4 has started\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Request all needed resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RQ Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New need array:&nbsp; &nbsp; &nbsp;    0 0 0 0\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New allocation array:&nbsp; &nbsp; &nbsp;    5 6 7 5\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	New available array:&nbsp; &nbsp; &nbsp;    5 0 0 3\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	State still safe: Yes\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread 4 has finished\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Thread is releasing resources\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	RL Request granted.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	Now available:&nbsp; &nbsp; &nbsp;    10 6 7 8
	
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
