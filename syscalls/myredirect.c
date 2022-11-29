#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int main() 
{
	int pid;
	pid = fork();
	if (pid == 0) 
	{
		close(1); //close stdout
		open("test", O_WRONLY | O_CREATE); // open a new file descriptor for a file (name: out)
		char *argv[] = {"echo", "this", "is", "redirected", "echo", 0};
		exec("echo", argv);
		printf("exec failed!\n");
		exit(0);
	} 
	else 
		wait(0);
	exit(0);
}
