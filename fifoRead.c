//Illustration of FIFO Read
//Run both the fifoRead.c and fifoWrite.c, Else one of the process will be blocked
//Runs only when both ends of fifo is opened 


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	int res = mkfifo("fifoFile",0777);
	if (res == -1)
	{
		if(errno != EEXIST)
			printf("Error creating FIFO\n");
	}

	int fd = open("fifoFile",O_RDWR);
	printf("Reading from fifoFile..\n");
	char buff[100];
	while(1){
		int res = read(fd,buff,sizeof(buff));
		if(strcmp(buff,"end") == 0)
			break;
		printf("%s\n",buff);
	}
	printf("Reading Done!\n");
	
	// int x;
	// read(fd,&x,sizeof(x));
	// printf("Read from FIFO: %d\n",x);
	
	close(fd);

	int fd1 = open("fifoFile",O_WRONLY);
	strcpy(buff,"ByeBye");
	write(fd,buff,sizeof(buff));
	printf("Writing Done\n");
	close(fd1);


	return 0;
}
