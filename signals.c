//Program to illustrate Signals

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	int pid = fork();
	if(pid == -1){
		printf("Fork Error\n");
		return -1;
	}

	if(pid == 0){
		while(1){
			printf("Child process Executing\n");
			usleep(50000);
		}

	}else{
		kill(pid,SIGSTOP); //stops/pauses the child process
		int t;
		do{
			printf("Enter the Time in seconds to execute Child: \n");
			scanf("%d",&t);
			if(t>0){
				kill(pid,SIGCONT);  //continues execution of child
				sleep(t);
			}
			kill(pid,SIGSTOP);
		}while(t>0);

		kill(pid,SIGKILL);
		printf("Parent killed Child process!!!\n");

		wait(NULL);	
	}


	return 0;
}
