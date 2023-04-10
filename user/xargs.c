#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[]){
	char * ch_argv[MAXARG];
	char buf[1];
	int i, j;

	for(i = 1, j = 0; i < argc; i++)
			ch_argv[j++] = argv[i];
	
	i = 0;
	ch_argv[j] = malloc(512);
	
	while(read(0, buf, 1) == 1){
		switch(buf[0]){
				case '\n': 
						{
							if(fork()==0){
								exec(argv[1], ch_argv);
								exit(0);
							}
							wait(0);
							for(int k = argc-1; k <= j; k++){
								memset( ch_argv[k], 0, 512);
								free(ch_argv[k]);
							}
							j = argc - 1;
							ch_argv[j] = malloc(512);
							i = 0;
							break;
						}
				case ' ':
						{
							i = 0;
							if(j<MAXARG) ch_argv[++j] = malloc(512);
							break;
						}
				default:
						{
							ch_argv[j][i++] = buf[0];
							break;
						}
				
		}		
	}
	exit(0);
}
