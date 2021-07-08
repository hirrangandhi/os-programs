//Parent creates Child 1 and Child 2

//Child 2 sends data to Parent
//Parent sends data to Child1 and Child1 prints the data

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>

int main(int argc, char const *argv[])
{
	int fd1[2],fd2[2];
	if(pipe(fd1) == -1){
		printf("Pipe 1 error\n");
		return -1;
	}
	if(pipe(fd2) == -1){
		printf("Pipe 2 error\n");
		return -1;
	}

	int id1 = fork();
	if(id1 == -1){
		printf("Fork 1 error\n");
		return -1;
	}

	if(id1 == 0){
		//Child 1
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);

		char msg[100];

		read(fd1[0],msg,sizeof(msg));
		msg[strlen(msg)] = '\0';

		printf("Child 1: Read \"%s\"\n",msg);
		
		close(fd1[0]);
		return 0;
	}

	int id2 = fork();
	if(id2 == -1){
		printf("Fork 1 error\n");
		return -1;
	}

	if (id2 == 0)
	{
		//Child 2
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);

		char msg[100];
		printf("Input String: ");
		fgets(msg,100,stdin);
		msg[strlen(msg)-1] = '\0';

		write(fd2[1],msg,strlen(msg));
		printf("Child 2: Sent \"%s\"\n",msg);

		close(fd2[1]);
		return 0;
	}

	//Parent
	close(fd1[0]);
	close(fd2[1]);
	waitpid(id2,NULL,0);

	char msg[100];
	read(fd2[0],msg,sizeof(msg));
	printf("Parent: Received \"%s\"\n",msg);

	strcat(msg," From Parent");
	msg[strlen(msg)] = '\0';
	write(fd1[1],msg,strlen(msg));
	printf("Parent: Sent \"%s\"\n",msg);

	waitpid(id1,NULL,0);
	close(fd1[1]);
	close(fd2[0]);
	

	return 0;
}