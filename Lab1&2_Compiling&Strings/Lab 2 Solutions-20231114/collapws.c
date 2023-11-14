/*
 * usage: ./collapws file
 *
 * copies standard input to standard output, collapsing sequences of white
 * space characters (as determined by isspace()) to a single blank character ' '
 *
 * sequences of white space characters in quoted strings are NOT collapsed
 */
#include <stdio.h>
#include <ctype.h>

#define INQUOTE 2	/* in quoted string */
#define IN 1		/* in a sequence of non-white space characters */
#define OUT 0		/* not in token */

#define UNUSED __attribute__ ((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
   int c, state;

   state = OUT;
   while ((c = getchar()) != EOF) {
      if (state == INQUOTE) {
         putchar(c);
	 if (c == '"')
            state = OUT;
      } else if (state == IN) {
         if (isspace(c)) {
            state = OUT;
            putchar(' ');
	 } else if (c == '"') {
            putchar(c);
	    state = INQUOTE;
         } else {
            putchar(c);
         }
      } else {		/* state == OUT */
         if (! isspace(c)) {
            putchar(c);
	    if (c == '"')
               state = INQUOTE;
	    else
               state = IN;
         }
      }
   }
   putchar('\n');
   return 0;
}
