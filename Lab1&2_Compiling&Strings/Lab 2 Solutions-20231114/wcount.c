#include <stdio.h>
#include <ctype.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* count words, where a word is a sequence of letters */
int main()
{
	long long nw = 0LL;
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF)
		if (! isalpha(c))
			state = OUT;
		else if (state == OUT) {
			state = IN;
			nw++;
		}
	printf("%lld\n", nw);
	return 0;
}
