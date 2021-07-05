//Splitting up the sum of array using 3(1-main and 2-child) processes
//And getting the results of child processes to main process using pipe

//Error in writing pipes

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int fd1[2],fd2[2];

	if (pipe(fd1) == -1)
	{
		printf("Error opening Pipe 1\n");
		return 2;
	}

	if (pipe(fd2) == -1)
	{
		printf("Error opening Pipe 2\n");
		return 2;
	}

	int arr[] = {1,2,3,4,5,6,7,8,9,1,2,3};
	int start,end;
	int sum;
	int size = sizeof(arr)/sizeof(int);
	int id1 = fork();
	int id2,val,totalSum;

	if(id1 == 0){
		start = 0;
		end = size/4;
	}
	else{
		id2 = fork();
		if(id2 == 0){
			start = size/4;
			end = size/2;
		}else{
			start = size/2;
			end = size;
			totalSum = 0;
		}
	}
	sum = 0;
	for (int i = start; i < end; ++i)
	{
		sum += arr[i];
	}
	printf("Partial sum is %d\n",sum);
	wait(NULL);
	if(id2 == 0){
		close(fd2[0]);
		printf("\tID2 Sum : %d\n",sum );
		write(fd2[1],&sum,sizeof(sum));
		close(fd2[1]);
	}
	else if(id2 != 0){
		wait(NULL);
		close(fd2[1]);
		read(fd2[0],&val,sizeof(val));
		totalSum = sum + val;
		//printf("Sum : %d\n",sum );
		printf("totalSum of id2: %d\n",totalSum);
		close(fd2[0]);
	}


	if(id1 == 0){
		sleep(2);
		close(fd1[0]);
		printf("\t ID1 Sum : %d\n",sum);
		write(fd1[1],&sum,sizeof(sum));
		close(fd1[1]);
	}
	else if (id1 != 0){
		sleep(2);
		wait(NULL);
		close(fd1[1]);
		read(fd1[0],&val,sizeof(val));
		totalSum = val + sum;
		//printf("Sum : %d\n",sum );
		printf("totalSum of id1: %d\n",totalSum);
		close(fd1[0]);
	}
	
	return 0;
}
