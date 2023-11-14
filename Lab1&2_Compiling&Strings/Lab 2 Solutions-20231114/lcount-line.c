/*
 * counts lines using readline()
 *
 * note that this will not give the correct result if any line exceeds
 * MAXLINE-1 characters
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int readline(char line[], int max);

int main()
{
	char buf[MAXLINE];
	long long nl = 0LL;

	while (readline(buf, MAXLINE))
		nl++;
	printf("%lld\n", nl);
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
