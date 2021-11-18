#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args(char *line){
	int s;
	int i = 0;
	for (s = 0; s<strlen(line); s++){
		if (line[s] == ' '){
			i++;
		}
	}
	i++;
	char **p = malloc((i+1)*sizeof(char *));
	char *l = line;
	s = i;
	i = 0;
	for (s>=0; s--;){
		char *c = strsep(&l, " ");
		p[i] = c;
		i++;
	}
	p[i] = NULL;
	return p;
}
