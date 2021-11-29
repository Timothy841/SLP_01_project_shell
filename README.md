Features: The shell implements the basic separation of commands by semicolons. It also can do redirection, though only one per command that's separated by semicolons. Also doesn't work unless it's separated by spaces.
Attempted features: None
Bugs: Piping works, but it prints the input program's things into stdout as well.

Function Headers:
int stringlen(char *line);//amount of arguments in a command. Takes a string and returns the number of spaces. Main takes care of spaces before an argument and parse_args takes cares of spaces after, so it works, but it's still not a true argument counter.
int semilen(char *line);//how many semicolons there are. Goes through a string and counts the number of semicolons. Doesn't count ones in quotes because those aren't meant to be separating semicolons.
int semipos(char *line);//returns index of first semicolon. Same as semilen, but returns a different thing.
void stringsplit(char *line, int pos);//splits line into two. Takes a string and an index and puts a NULL there to separate it.
char ** parse_args(char *line);//turns a string into an array of strings. Only does the first part and leaves the second part as a string. Separates the parts based on semicolons. The first part is separated using strsep on spaces. When there are additional spaces, the strlen is 0, so I don't add those.
char * restring(char **strings);//puts array of strings back into a single string. For piping. Strcats each string and a spaces unless it's the last argument.
int redirect(char **strings);//redirection and pipes. Takes an array of string that was parsed and looks at each string to see if it's >, >>, <, or |. If it is, it restrings the array and does the redirection or piping.
