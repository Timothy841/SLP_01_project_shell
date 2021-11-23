#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int stringlen(char *line){
	int i = 0;
	for (int s = 0; s<strlen(line); s++){
		if (line[s] == ' '){
			i++;
		}
	}
	return i+1;
}

int semilen(char *line){
	int i = 0;
	for (int s = 0; s<strlen(line); s++){
		if (line[s] == ';'){
			i++;
		}
	}
	return i+1;
}

void nextsemi(char *line){
	for (int s = 0; s<strlen(line); s++){
		if (line[s] == ';'){
			strcpy(line, &line[s+2]);
			break;
		}
	}
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
		if (s && l[0] == ';'){
				break;
		}
	}
	p[i] = NULL;
	return p;
}
