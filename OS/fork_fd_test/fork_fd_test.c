#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 

int main() 
{
	pid_t pid;
  	int status; 
	int fd_read; 
	int fd_write; 
	ssize_t nrd; 
  	char *buffer = malloc(100*sizeof(char)); 

	switch (pid = fork()) 
	{
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("Child process -My PID:%d, My parent's PID:%d\n", (int)getpid(), (int)getppid());
			printf("opening the files.."); 
			fd_read = open("test.txt", O_RDONLY); // the file we just created with echo rediction
			fd_write = open("test2.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR); 
			while (nrd = read(fd_read, buffer, sizeof(buffer)))
				write(fd_write, buffer, nrd); 
          	//sleep(100000);	
			close(fd_read);
			close(fd_write); 	
			printf("closed all files"); 			
			exit(0); 	
			break;
		default:
			printf("Parenet process -My PID:%d, My Parent's PID: %d, My Child's PID: %d\n", (int)getpid(), (int)getppid(), (int)pid);
			wait(&status); 
			exit(0); 
			break;
	}
	free(buffer); 
	printf("End of fork\n"); 
	exit(0); 
}
			


