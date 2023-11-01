#include <stdio.h>

int funcN2(char *a, char *b, char *ret)
{
    int i, j, k = 0;

    for (i = 0; a[i] != '\0'; i++)
    {
        for (j = 0; b[j] != '\0'; j++)
        {
            if (a[i] == b[j])
            {
                ret[k] = a[i];
            }
        }
    }
    
    return 0;
}

int funcN(char *a, char *b, char *ret)
{
    int i, j, k = 0;
    int letras[26];

    for (i = 0; i < 26; i++)
    {
        letras[i] = 0
    }
    

    for (i = 0; a[i] != '\0'; i++)
    {
        
    }
    
}

int main()
{

}