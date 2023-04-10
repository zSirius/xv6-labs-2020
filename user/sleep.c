#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int num;

	if(argc != 2){
		fprintf(2, "must 1 argument for sleep!\n");
		exit(1);
	}

	num = atoi(argv[1]);
	fprintf(1, "(nothing happens for a little while)\n");
	sleep(num);

	exit(0);
}
