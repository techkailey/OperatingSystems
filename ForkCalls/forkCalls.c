// CSCI 4401 Fork Assignment 
// Kailey Bergeron 
// September 2024

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
	int userInput;
	int i;
	int pid;
	int pid2;
	FILE *outputFile;

	// opens output file in write mode
	outputFile = fopen("Question2.txt", "w");

	printf("Enter number of fork() calls, must be an integer greater than 0: ");
	// get value of userInput
	scanf("%d",&userInput);
	printf("Entered: %d \n", userInput);
	printf("Initial PID: %d, Parent PID: %d \n\n", getpid(), getppid());

	// fork n times per user input
	for(i=1; i<=userInput; i++){
		pid = fork();
		if(pid == 0){
		
		}else {
			pid2 = getppid();
			if(pid == pid2) {
				waitpid(-1, NULL, 0);
			}
		}
	}

	fprintf(outputFile, "PID: %d, PPID: %d \n", getpid(), getppid());
        //close output file in parent process
        fclose(outputFile);
}
