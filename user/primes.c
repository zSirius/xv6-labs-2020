#include "kernel/types.h"
#include "user/user.h"

void primes(int p1[], int p2[]){
	if(fork() == 0){
		int num;
		if(read(p1[0], &num, sizeof(num)) != sizeof(num)){
			close(p1[0]);
			close(p2[0]);
			close(p2[1]);
			exit(0);
		}
		int p = num;
		printf("prime %d\n", num);

		while( read( p1[0], &num, sizeof(num) == sizeof(num) ) ){
			if(num%p != 0){
				write(p2[1], &num, sizeof(num));
			}
		}
		
		close(p1[0]);
		close(p2[1]);

		pipe(p1);
		primes(p2,p1);
		exit(0);
	
	}else {
		close(p1[0]);
		close(p2[0]);
		close(p2[1]);
		wait(0);
		exit(0);
	}
}


int main(){
	int p1[2], p2[2], i;
	pipe(p1);
	pipe(p2);
	
	for(i=2; i<=35; i++)
		write(p1[1], &i, sizeof(i));
	
	close(p1[1]);
	primes(p1, p2);

	exit(0);
}
