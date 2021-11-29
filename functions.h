int stringlen(char *line);
int semilen(char *line);
int semipos(char *line);
void stringsplit(char *line, int pos);
char ** parse_args(char *line);
char * restring(char **strings);
int redirect(char **strings);
