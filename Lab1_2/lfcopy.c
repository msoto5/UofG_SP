#include <stdio.h>
#include <string.h>

#define MAXL 50

int readline(char line[], int max);
int writeline(const char line[]);

int main()
{
    char line[MAXL];

    if (readline(line, MAXL) == 0)
    {
        return 1;   
    }
    printf("num -> %d\n", writeline(line));
    
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
/* writeline: write line to standard output, return number of chars
written */
int writeline(const char line[])
{
    fputs(line, stdout);
    return strlen(line);
}