#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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

int semipos(char *line){//returns index of first semicolon
	int quotes = 0;
	int s;
	for (s = 0; s < strlen(line); s++){
		if (line[s] == ';' && quotes%2 == 0){
			return s;
		}
		else if (line[s] == '"'){
			quotes++;
		}
	}
	return s;
}

void stringsplit(char *line, int pos){//splits line into two
	line[pos] = '\0';//split line by introducing a null
}

char ** parse_args(char *line){//turns a string into an array of strings. Only does the first part and leaves the second part as a string. Separates them based on semicolons
	int semi = semipos(line);//index of semicolon
	stringsplit(line, semi);//split using semicolon
	int s = stringlen(line);//number of arguments in first part
	char **p = malloc((s+1)*sizeof(char *));
	int i = 0;
	for (s>0; s--;){
		char *string = strsep(&line, " ");
		sscanf(string, "%s\n", string);
		if (strlen(string)){
			p[i] = string;
			i++;
		}
	}
	if (p[i-1][0] == '\n'){
		p[i-1] = NULL;
	}
	else{
		p[i] = NULL;
	}
	return p;
}

char * restring(char **strings){//put array of strings back into a single string. For piping
	char *line = calloc(20, 10);
	for (int i = 0; strings[i] != NULL; i++){
		strcat(line, strings[i]);
		if (strings[i+1] != NULL){
			strcat(line, " ");
		}
	}
	return line;
}

int redirect(char **strings){//redirection and pipes
	int a = 0;
	while (strings[a] != NULL){//go through until the end
		if (!strcmp(strings[a], ">")){
			int file = open(strings[a+1], O_WRONLY | O_CREAT, 0644);//open file to write
			int tempout = dup(STDOUT_FILENO);//duplicate of stdout
			dup2(file, STDOUT_FILENO);//set stdout's entry to file
			char *temppointer = strings[a];
			strings[a] = NULL;
			int sf = execvp(strings[0], strings);//only looks at first half
			strings[a] = temppointer;
			dup2(tempout, STDOUT_FILENO);//set stdout's entry back to stdout
			close(file);
			close(tempout);
			return 0;
		}
		else if (!strcmp(strings[a], ">>")){
			int file = open(strings[a+1], O_APPEND | O_CREAT, 0644);//open file to append
			int tempout = dup(STDOUT_FILENO);//duplicate of stdout
			dup2(file, STDOUT_FILENO);//set stdout's entry to file
			char *temppointer = strings[a];
			strings[a] = NULL;
			int sf = execvp(strings[0], strings);//only looks at first half
			strings[a] = temppointer;
			dup2(tempout, STDOUT_FILENO);//set stdout's entry back to stdout
			close(file);
			close(tempout);
			return 0;
		}
		else if (!strcmp(strings[a], "<")){
			int rfile = open(strings[a+1], O_RDONLY);//open file to read from
			int tempout = dup(STDIN_FILENO);//duplicate of stdin
			dup2(rfile, STDIN_FILENO);//set stdin's entry to file
			char *temppointer = strings[a];
			strings[a] = NULL;
			int sf = execvp(strings[0], strings);
			strings[a] = temppointer;
			dup2(tempout, STDIN_FILENO);//set stdin's entry back to stdout
			close(rfile);
			close(tempout);
			return 0;
		}
		else if (!strcmp(strings[a], "|")){
			strings[a] = NULL;
			char *first = restring(strings);//first half
			char *second = restring(&strings[a+1]);//second half
			FILE *read = popen(first, "r");
			FILE *write = popen(second, "w");
			if (read == NULL || write == NULL){
				printf("Something went wrong please try again\n");
				exit(0);
			}
			while (1) {
				if (feof(read)) {//reached end of read
					break;
				}
				fputc(fgetc(read),write);//put each character of read into write
			}
			pclose(write);
			pclose(read);
			free(first);
			free(second);
			return 0;
		}
		a++;
	}
	return 1;
}
