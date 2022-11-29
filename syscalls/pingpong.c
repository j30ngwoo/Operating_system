#include "kernel/types.h"
#include "user/user.h"

int main() 
{
	int fd1[2], fd2[2], pid;
	char buf[100];
	// create a pipe, with two FDs in fds[0], fds[1].
	pipe(fd1);
	pipe(fd2);
	pid = fork();
	if (pid == 0) 
	{
		read(fd1[0], buf, sizeof(buf));
		printf("%d: received %s\n", getpid(), buf);
		write(fd2[1], "pong", 4);
	}
	else 
	{
		write(fd1[1], "ping", 4);
		read(fd2[0], buf, sizeof(buf));
		printf("%d: received %s\n", getpid(), buf);
	}
	exit(); 
}