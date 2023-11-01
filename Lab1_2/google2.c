#include <stdio.h>

int func(int *a, int n, int *out)
{
    int i, mul, mul0;

    mul0 = 1;
    mul = 1;
    for (i = 0; i < n; i++)
    {
        mul *= a[i];
        if (i > 0)
        {
            mul0 *= a[i];
        }
        
        out[(i+1)%n] = mul;
    }
    
    [10, 2, 3, 4, 5, 6]
    [7200, 10, 20, 60, 240, 1200]
     720    1,  2,  6,  24,  120 
}

int main()
{

}