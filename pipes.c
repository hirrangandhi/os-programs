//Sample program for Pipes
// pd[0] for READ and pd[1] for WRITE

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(){
	int pd[2];
	if(pipe(pd) == -1){
		printf("pd not created");
		return -1;
	}
	
	int f = fork();
	//char msg[20],i[10];
	if(f > 0){
		close(pd[0]);
		printf("Parent Process\n");
		char msg[20];
		//strcpy(msg,"hello world");
		printf("Enter data: ");
		scanf("%s",msg);
		write(pd[1],msg,sizeof(msg));
		printf("Writing Done!\n");
		
	}
	else{
		close(pd[1]);
		//wait(NULL);
		printf("Child Process\n");
		char i[10];
		read(pd[0],i,sizeof(i));
		printf("Read from Pipe: %s",i);
	}


	return 0;
}
