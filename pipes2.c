//Two way communication between two processes using pipes

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>

int main(int argc, char const *argv[])
{
	int pd[2]; //P -> C
	int cd[2]; //C -> P

	if(pipe(pd) == -1){
		printf("Error opening Pipe 1\n");
	}

	if(pipe(cd) == -1){
		printf("Error opening Pipe 2\n");
	}

	int id = fork();

	if(id == 0){
		close(cd[0]);
		close(pd[1]);
		//printf("Child\n");
		int x;
		if(read(pd[0],&x,sizeof(x)) == -1){
			printf("Read Error in Child\n");
			return -1;
		}
		printf("\tFrom Parent: %d\n",x);
		x *= 2;
		if(write(cd[1],&x,sizeof(x)) == -1){
			printf("Write error in Child\n");
			return -1;
		}
		close(cd[1]);
		close(pd[0]);

	}
	else{
		close(pd[0]);
		close(cd[1]);
		//printf("Parent\n");
		srand(time(0));
		int num,x;
		num = rand()%10;
		if(write(pd[1],&num,sizeof(int)) == -1){
			printf("Write error in Parent");
			return -1;
		}
		wait(NULL);
		if(read(cd[0],&x,sizeof(x)) == -1){
			printf("Read Error in Parent\n");
			return -1;
		}
		printf("From Child:Doubled value of num: %d is %d\n",num,x);
		close(pd[1]);
		close(cd[0]);


	}
	
	return 0;
}
