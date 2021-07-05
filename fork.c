//Sample program for fork()

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main(){
	pid_t f = fork();
	if(f == 0){
		printf("Child Process %d\n",getpid());
	}
	else{
		printf("Parent Process %d\n",getpid());
	}


	return 0;
}
