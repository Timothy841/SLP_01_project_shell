#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"


int main(){//make ls work with bunch of spaces
	int f = 1;
    	int status, p;
	char c[200];
	while (f){//parent keeps running
		printf("Parent: ");
		fgets(c, sizeof(c), stdin);
		char **string = parse_args(c);
		f = fork();
		if (strcasecmp(c, "cd") == 0){
		}
		if (f == 0){//child
			execvp(string[0], string);
			return 0;
		}
		printf("%s\n", getcwd(c, sizeof(c)));
    		p = waitpid(-1, &status, 0);
		if (WIFEXITED(status)){
		}
	}
	return 1;
}


