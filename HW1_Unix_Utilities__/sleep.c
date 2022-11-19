//user/sleep.c 
#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(2, "usage: sleep [ms] \n");
		exit();
	}
	int sleep_time = atoi(argv[1]);
	sleep(sleep_time);
	exit();
}