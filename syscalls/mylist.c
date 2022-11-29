#include "kernel/types.h"
#include "user/user.h"

struct dirent {
	ushort inum;
	char name[14];
};

int main()
{
	int fd;
	struct dirent e;
	fd = open("test", 0);
	while(read(fd, &e, sizeof(e)) == sizeof(e))
		if(e.name[0] != '\0')
			printf("%s\n", e.name);
	exit(0);
}
