#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int readline(char line[], int max);
int writeline(const char line[]);

int main()
{
	char buf[MAXLINE];

	while (readline(buf, MAXLINE))
		writeline(buf);
	return 0;
}

/* readline: read a line from standard input, return its length or 0 */
int readline(char line[], int max)
{
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

/* writeline: write line to standard output, return number of chars written */
int writeline(const char line[])
{
	fputs(line, stdout);
	return strlen(line);
}
