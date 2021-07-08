//Child process generate random numbers and send them to the parent
//Parent sums all the numbers and print the result


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>

int main(int argc, char const *argv[])
{	
	int fd[2];
	if(pipe(fd) == -1){
		printf("Pipe error\n");
		return -1;
	}

	int pid = fork();
	if(pid == -1){
		printf("Fork error\n");
		return -1;
	}

	if(pid == 0){
		//Child
		close(fd[0]);
		srand(time(NULL));
		int arr[100];
		int i,n;

		printf("Enter size of array (less than 100): ");
		scanf("%d",&n);

		
		printf("From Child: Generated ");
		for(i=0;i<n;++i){
			arr[i] = rand()%10 + 1;
			printf("%d ",arr[i]);
		}
		printf("\n");
		write(fd[1],&n,sizeof(n));
		printf("From Child: Sent n = %d\n",n);
		write(fd[1],arr,sizeof(arr));
		printf("From Child: Sent array\n");

		close(fd[1]);
	}
	else{
		//Parent
		close(fd[1]);
		wait(NULL);
		int arr[100];
		int n,i,sum;

		read(fd[0],&n,sizeof(n));
		printf("From Parent: Received n = %d\n",n);
		
		read(fd[0],arr,n * sizeof(int));
		printf("From Parent: Received Array\n");
		
		for (i = 0,sum = 0; i < n; ++i)
		{
			//printf("%d ",arr[i]);
			sum += arr[i];
		}
		printf("From Parent: Sum of Array is : %d\n",sum);
		
		close(fd[0]);
	}


	return 0;
}