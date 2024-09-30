// CSCI 4401 - Message Passing
// Kailey Bergeron 
// September 2024

#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

// declares msg queue structure
struct mesg_buffer {
	long type;
	char text[100];
};

int main(){
	struct mesg_buffer buf;
	key_t key;
	int msgid;
	pid_t pid;

	// ftok generates unique key
	key = ftok(".", 'x');

	// creates message queue and returns ID
	msgid = msgget(key, 0666 | IPC_CREAT);

	pid = fork();

	if(pid == 0){
		// ensure parent goes first
		sleep(1);
		if(msgrcv(msgid, &buf, sizeof(buf),1, 0)!= -1){
	        	printf("I am child %d. My chore is %s", getpid(), buf.text);
       			printf("I finsihed my chore. Sending my parent: \n");
        		fgets(buf.text, sizeof buf.text, stdin);
        		// send reply back to parent
			buf.type = 2;
        		msgsnd(msgid, &buf, sizeof(buf.text), 0);
        		printf("I sent my parent a reply. \n\n");
		}
	} else if(pid > 0) {
		printf("I am parent %d. Please do the following chore: \n", getpid());
		fgets(buf.text, sizeof(buf.text), stdin);
		buf.type = 1;
		// send chore to child
		msgsnd(msgid, &buf, sizeof(buf.text), 0);
		printf("Chore has been sent. \n\n");

		// receive reply from child
		if(msgrcv(msgid, &buf, sizeof(buf.text), 2, 0)!= -1){
			printf("I am parent %d. \nI received from my child: %s", getpid(), buf.text);
		}
	}

	msgctl(msgid, IPC_RMID, NULL);
	
	return 0;
}
