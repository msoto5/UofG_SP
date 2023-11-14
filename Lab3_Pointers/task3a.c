#include <stdio.h>

#define WORDS_MAX 50

void reverse_print(char **p, int n);

int main()
{
    char *message[WORDS_MAX] = {"I", "think", "we’ve", "got", "our", "roles", "reversed"};

    reverse_print(message, 3);

    reverse_print(message, WORDS_MAX);

    return 0;
}

void reverse_print(char **p, int n)
{
    // Error control
    if (!p || n < 0 || n >  WORDS_MAX)
    {
        return;
    }
    
    for (n--; n >= 0; n--)
    {
        if (p[n])
        {
            printf("%s ", *(p+n));
        }
    }
    printf("\n");
    
    return;
}

