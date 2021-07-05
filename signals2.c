//Signal Handling

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void handle_SIGTSTP(int signum){
	printf("Stop is not allowed\n");
}


void handle_SIGCONT(int signum){
	printf("Input Number : ");
}

int main(int argc, char const *argv[])
{
	struct sigaction s1;				//Standard version
	s1.sa_handler = &handle_SIGTSTP;
	s1.sa_flags = SA_RESTART;
	sigaction(SIGTSTP,&s1,NULL);

	//signal(SIGTSTP,&handle_SIGTSTP); //behavior varies on different versions

	//signal(SIGCONT,&handle_SIGCONT);

	int num;
	printf("Enter a number: ");
	scanf("%d",&num);
	printf("The number is %d\n",num);

	return 0;
}
