//Illustration of FIFO Write
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

	int fd = open("fifoFile",O_CREAT|O_WRONLY);
	char buff[100];
	
	printf("Write content to file:\n");
	printf("Type \"end\" to stop\n");
	while(1){
		scanf("%s",buff);
		write(fd,buff,sizeof(buff));
		if(strcmp(buff,"end") == 0)
			break;
	}
	printf("Writing Done!\n");
	
	// int x = 97;
	// write(fd,&x,sizeof(x));
	// printf("Writing Done!\n");

	close(fd);
	sleep(2);

	int fd1 = open("fifoFile",O_RDONLY);
	read(fd1,buff,sizeof(buff));
	printf("Read : %s\n",buff);
	close(fd1);


	return 0;
}
