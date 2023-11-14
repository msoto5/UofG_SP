#include <stdio.h>
#include <ctype.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* writes each word from standard input, one per line, on standard output */
int main()
{
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF)
		if (isalpha(c)) {
			putchar(c);
			state = IN;
		} else {
			if (state == IN)
				putchar('\n');
			state = OUT;
		}
	if (state == IN)
		putchar('\n');
	return 0;
}
