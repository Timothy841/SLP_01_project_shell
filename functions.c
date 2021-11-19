#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int stringlen(char *line){
	int s;
	int i = 0;
	for (s = 0; s<strlen(line); s++){
		if (line[s] == ' '){
			i++;
		}
	}
	return i+1;
}

char ** parse_args(char *line){
	int s = stringlen(line);
	char **p = malloc((s+1)*sizeof(char *));
	char *l = line;
	int i = 0;
	for (s>=0; s--;){
		if (s){
			char *c = strsep(&l, " ");
			p[i] = c;
			i++;
		}
		else{
			char *c = strsep(&l, " ");
			sscanf(c, "%s\n", c);
			p[i] = c;
			i++;
		}
	}
	p[i] = NULL;
	return p;
}
