#include <stdio.h>

/*
 * count lines on stdin and print results on stdout
 * counts last line even if it is not terminated by a newline character
 */
int main()
{
	int c;
	int lastc = '\n';
	long long nlines = 0LL;

	while ((c = getchar()) != EOF) {
		lastc = c;
		if (c == '\n')
			nlines++;
	}
	if (lastc != '\n')
		nlines++;
	printf("%lld\n", nlines);
	return 0;
}
