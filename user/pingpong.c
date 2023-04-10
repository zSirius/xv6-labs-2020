#include "kernel/types.h"
#include "user/user.h"

int
main(){
	int p1[2], p2[2];
	char buf[1] = {'a'};
	long len = sizeof(buf);
	pipe(p1);
	pipe(p2);

	
	if(fork()==0){
		close(p1[1]);
		close(p2[0]);
		if(read(p1[0], buf, len) != len){
			printf("read from parent is error!\n");
			exit(1);
		}
		printf("%d: received ping\n", getpid());

		if(write(p2[1], buf, len) != len){
			printf("write to parent is error!\n");
			exit(1);
		}
		close(p1[0]);
		close(p2[1]);	
	}else{
		close(p1[0]);
		close(p2[1]);
		if(write(p1[1], buf, len) != len){
			printf("write to child is error!\n");
			exit(1);
		}
		if(read(p2[0], buf, len) != len){
			printf("read from child is error!\n");
			exit(1);
		}
		printf("%d: received pong\n", getpid());
		close(p1[1]);
		close(p2[0]);
	}
	exit(0);
}
