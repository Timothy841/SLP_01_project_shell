#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "functions.h"


int main(){
	int f = 1;
  int status, p;
	char c[200];
	while (f){//parent keeps running
		printf("Parent: ");
		fgets(c, sizeof(c), stdin);
		char *cc = c;
		int end = strlen(c)-1;
		for (int i = semilen(c); i>0; i--){
			int next = semipos(cc)+1;
			char **string = parse_args(cc);
			if (strcasecmp(string[0], "cd") == 0){//cd
				if (string[1]){
					char directory[200];
					printf("Old directory: %s\n", getcwd(directory, sizeof(directory)));
					chdir(string[1]);
					printf("New directory: %s\n", getcwd(directory, sizeof(directory)));
				}
			}
			else if (strcasecmp(string[0], "exit") == 0){//exit
				exit(0);
			}
			else{//other commands
				f = fork();
				if (f == 0){//child
					int a = redirect(string);//if a is a number, that means it's redirect, don't execvp
					if (a == 1){
						execvp(string[0], string);
						if (errno == 2){
							printf("Command doesn't work\n");
						}
					}
					return 0;
				}
				else{//parent
					waitpid(-1, &status, 0);
				}
			}
			if (next >= end){
				break;
			}
			cc = &cc[next];//brings cc to next set of commands
			while (cc[0] == ' '){
				cc = &cc[1];
			}
		}
	}
	return 0;
}


//sscanf everything to get rid of spaces. If string is just a space or it becomes null, dpn't add it.
