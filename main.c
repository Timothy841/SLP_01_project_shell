#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"


int main(){
	int f = 1;
	while (f){//parent keeps running
		f = fork();
		if (f){//parent
	    		int status;
	    		int a = waitpid(-1, &status, 0);
			if (WIFEXITED(status)){
				printf("Parent:\n");
			}
		}
		else{//child
		printf("Child:\n");
		char c[20];
		read(STDIN_FILENO, c, sizeof(c));
		printf("%s\n", c);
		}
	}
	return 1;
}
