#include <stdio.h>

int read(char *c)
{
    fflush(stdin);
    if (scanf("%c", c) < 0)
    {
        return 0;
    }
    
    return 1;
}

int main()
{
    char c;

    while (read(&c) > 0)
    {
        if (c != '\n')
        {
            printf("%c\n", c);
        }
        
    }
    
    return 0;
}