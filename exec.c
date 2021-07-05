//execlp, Wait status, dup2 program

/*
file descriptors 		file
0(STDIN_FILENO)			STDIN
1(STDOUT_FILENO)		STDOUT
2						STDERR
3,4,5...				Represents user created files opened in program

dup(FD) -> returns another fd, which is duplicate of FD
dup2(fd1,fd2) -> replaces fd1 with fd2
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<time.h>
#include<fcntl.h>


int main(int argc, char const *argv[])
{	

	int id = fork();

	if(id == -1){
		printf("Error in Fork\n");
		return 1;
	}

	if(id == 0){
		//Child
		int file = open("pingResults.txt",O_CREAT|O_WRONLY,0777);
		if(file == -1){
			printf("Error creating file\n");
			return 2;
		}
		printf("The fd of pingResults.txt is %d\n",file);

		int file2 = dup2(file,STDOUT_FILENO); //Replaces Standard output with pingResults
		printf("The fd of duplicated file is %d\n",file2);
		close(file);

		int res = execlp("ping","ping","-c","5","google.com",NULL);
		if(res == -1){
			printf("Not able to execute\n");
			return 1;
		}
	}else{
		//Parent
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus)){  //Checks whether the process is exited normally
			int statusCode = WEXITSTATUS(wstatus); //Gets the Return value of the process
			if(statusCode == 0)
				printf("Success..!\n");
			else
				printf("Failure.!\n");
		}
		printf("Parent process is doing something\n");
	}

	return 0;
}
