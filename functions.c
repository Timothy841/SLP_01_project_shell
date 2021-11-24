#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int stringlen(char *line){//amount of arguments in a command
	int i = 0;
	for (int s = 0; s<strlen(line); s++){
		if (line[s] == ' '){
			i++;
		}
	}
	return i+1;
}

int semilen(char *line){//how many semicolons there are
	int i = 0;
	int quotes = 0;
	for (int s = 0; s < strlen(line); s++){
		if (line[s] == ';' && quotes%2 == 0){
			i++;
		}
		else if (line[s] == '"'){
			quotes++;
		}
	}
	return i+1;
}

int semipos(char *line){
	int quotes = 0;
	int s;
	for (s = 0; s < strlen(line); s++){
		if (line[s] == ';' && quotes%2 == 0){
			return s+1;
		}
		else if (line[s] == '"'){
			quotes++;
		}
	}
	return s+1;
}

char * stringsplit(char *line, int pos){//first half and second half
	line[pos] = '\0';//split line
	char *c = &line[pos+1];
	return c;//return latter half
}
/*char ** parse_args(char *line){
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
}*/

char ** parse_args(char *line){
	char *c = line;
	int quotes = 0;
	line = stringsplit(line, semipos(line));//line is now the second half	c is first half
	int s = stringlen(c);//s is how many arguments there are
	char **p = malloc((s+1)*sizeof(char *));
	char *l = c;
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
	return p;//returns the first half
}
