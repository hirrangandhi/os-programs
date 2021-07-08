//Working with multiple pipes

/*
	For n- processes, n- pipes

	2 * n -> file Descriptors
	2 * n^2 -> close calls

*/

//Main process generates a number X and send it to Child 1 through Pipe
//Child 1 multiples the X by 2 and send it to Child 2
//Child 2 again multiples X by 2 and send it to Main process

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>


int main(int argc, char const *argv[])
{
	int fd[3][2];

	for (int i = 0; i < 3; ++i)
	{
		if(pipe(fd[i]) == -1){
			printf("Pipe %d Error\n",i);
			return -1;
		}
	}

	int id1 = fork();
	if(id1 == -1){
		printf("Fork 1 error\n");
		return -1;
	}

	if(id1 == 0){
		//Child 1
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);	
		close(fd[2][1]);
		int x;
		read(fd[0][0],&x,sizeof(int));
		printf("Child 1: Read X = %d \n",x);
		x *= 2;
		write(fd[1][1],&x,sizeof(int));
		printf("Child 1: Sent X = %d\n",x);

		close(fd[0][0]);
		close(fd[1][1]);

		return 0; //Child process Ends. No need of Else block

	}

	int id2 = fork();
	if(id2 == -1){
		printf("Fork 2 Error\n");
		return -1;
	}

	if(id2 == 0){
		//Child 2
		close(fd[0][0]);
		close(fd[0][1]);	
		close(fd[1][1]);
		close(fd[2][0]);

		int x;
		read(fd[1][0],&x,sizeof(int));
		printf("Child 2: Read X = %d \n",x);
		
		x *= 2;
		write(fd[2][1],&x,sizeof(int));
		printf("Child 2: Sent X = %d\n",x);			

		close(fd[0][0]);
		close(fd[2][1]);

		return 0;
	}

	//Parent
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);	
	close(fd[2][1]);

	srand(time(NULL));
	int x = rand()%10 + 1;
	write(fd[0][1],&x,sizeof(int));
	printf("From Main: Sent X = %d\n",x);

	waitpid(id1,NULL,0);
	waitpid(id2,NULL,0);

	read(fd[2][0],&x,sizeof(int));
	printf("From Main: Read X = %d\n",x);

	close(fd[0][1]);
	close(fd[2][0]);


	return 0;
}