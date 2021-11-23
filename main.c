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
		for (int i = semilen(c); i>0; i--){
			char **string = parse_args(c);
				printf("[%s]\n", c);
			if (strcasecmp(string[0], "cd") == 0){
				if (string[1]){
					char directory[200];
					printf("Old directory: %s\n", getcwd(directory, sizeof(directory)));
					chdir(string[1]);
					printf("New directory: %s\n", getcwd(directory, sizeof(directory)));
				}
			}
			else if (strcasecmp(string[0], "exit") == 0){
				exit(0);
			}
			else{
				f = fork();
				if (f == 0){//child
					execvp(string[0], string);
					return 0;
				}
				else{//parent
					waitpid(-1, &status, 0);
				}
			}
			if (i > 1){
				printf("[%s]\n", c);
			}
		}
	}
	return 1;
}
