#include <stdio.h>
#include <stdlib.h>
 
int main()
{
   int x = 0;
   int inp = 0;
   int nums[20]; 
   int idx = 0;
   for(;;){
     printf("Enter an integer: ");
     inp=fscanf(stdin, "%d", &x);
     if(inp == 0){
       printf("Error: not an integer\n");
     }
     else{
       if(idx<20){
         nums[idx] = x;
         idx++;
       }
     } 
   }
   return 0;
}
