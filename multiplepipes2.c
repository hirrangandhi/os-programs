//Creates PROCESS_NUM number of processes.
//Each process have one set of pipe

//Main process send a number to first child and it goes through every child
//Every child will increment the number by 1 and finally send back to Mai process

/*
	For n- processes, n- pipes

	2 * n -> file Descriptors
	2 * n^2 -> close calls

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>

#define PROCESS_NUM 3

int main(int argc, char const *argv[])
{
	int pipes[PROCESS_NUM+1][2];

	for(int i=0; i<PROCESS_NUM+1; i++){
		if(pipe(pipes[i]) == -1){
			printf("Error opening pipe\n");
			return -1;
		}
	}

	for(int i=0; i<PROCESS_NUM; i++){
		int id = fork();
		if(id == 0){
			for(int j=0; j<PROCESS_NUM; j++){
				if(i != j){
					close(pipes[j][0]);
				}
				if(i+1 != j){
					close(pipes[j][1]);
				}
			}
			int x;
			read(pipes[i][0],&x,sizeof(int));
			printf("Child %d received %d\n",i,x);

			x ++;

			write(pipes[i+1][1],&x,sizeof(int));
			printf("Child %d sent %d\n",i,x);

			close(pipes[i][0]);
			close(pipes[i+1][1]);
			return 0;
		}
	}

	//Parent
	for(int j=0; j<PROCESS_NUM; j++){
		if(j != PROCESS_NUM){
			close(pipes[j][0]);
		}
		if(j != 0){
			close(pipes[j][1]);
		}
	}
	int x;
	srand(time(NULL));
	x = rand() % 10 + 1;
	write(pipes[0][1],&x,sizeof(int));
	printf("Main process sent %d\n",x);
	read(pipes[PROCESS_NUM][0],&x,sizeof(int));
	printf("Main process got %d\n",x);

	close(pipes[0][1]);
	close(pipes[PROCESS_NUM][0]);

	for (int i = 0; i<PROCESS_NUM; i++)
	{
		wait(NULL);
	}

	return 0;
}