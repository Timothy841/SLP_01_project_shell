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

char * stringsplit(char *line, int pos){
	line[pos] = '\0';//split line
	return &line[pos+1];//return latter half
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
	for (int s = 0; s < strlen(line); s++){
		if (line[s] == '"'){
			quotes++;
		}
		else if (line[s] == ';' && quotes%2 == 0){
			line = stringsplit(line, s);//line is now the second half
			printf("%svbv\n", line);
		}
	}
	int s = stringlen(line);
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
