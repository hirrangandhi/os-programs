//User defined Signal handling

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int x = 0;

void handle_SIGUSR1(int signum){
	if(x == 0)
		printf("(HINT) Type the sum of two numbers..!\n");
}

int main(int argc, char const *argv[])
{
	int id = fork();

	if(id == 0){
		//Child
		sleep(5);
		kill(getppid(),SIGUSR1);
	}
	else{
		//Parent
		struct sigaction sa;
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handle_SIGUSR1;
		sigaction(SIGUSR1,&sa,NULL);

		printf("Find the result of 3 + 2: \n");
		scanf("%d",&x);
		if(x == 5)
			printf("Correct Answer!\n");
		else
			printf("Wrong Answer!\n");
		wait(NULL);
	}


	return 0;
}
