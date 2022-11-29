#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int main()
{
	int fd = open("myopen_test", O_WRONLY | O_CREATE);
	write(fd, "gimotti\n", 8);
	exit(0);
}