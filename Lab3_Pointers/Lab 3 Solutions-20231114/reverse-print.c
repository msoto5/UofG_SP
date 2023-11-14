#include <stdio.h>
#include <stdlib.h>
#define WORDS_MAX 1000
void reverse_print(char **, int);

int main() {
   int n = 3;
   char *message[WORDS_MAX] = {"I", "think", "we've", "got", "our", "roles", "reversed"};
   reverse_print(message, n); //max: WORDS_MAX
   return 0;
}

void reverse_print(char **p, int n) {
   int count;
   for (count = n-1; count >= 0; count--) {
        if (p[count])
            printf("%s ", p[count]);
   }
   printf("\n");
}