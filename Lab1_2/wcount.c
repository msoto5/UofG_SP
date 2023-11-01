#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 50

int readline(char line[], int max);

int main()
{
    char l[MAXL];
    int i, k, f;
    
    if (readline(l, MAXL) == 0)
    {
        return 1;
    }
    
    k = 0;
    for (i = 0; l[i] != '\0'; i++)
    {
        if (isalpha(l[i]) && (i == 0 || l[i-1] == ' '))
        {
            f = 1;
        }
        else if (f == 1 && l[i] == ' ')
        {
            f = 0;
            k++;
        }
    }
    
    printf("num words -> %d\n", k);
    return 0;
}

/* readline: read a line from standard input, return its length or 0
 */
int readline(char line[], int max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}