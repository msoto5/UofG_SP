#include <stdio.h> 
#include <string.h>
#include <stdlib.h>


/*This is the naive method taking O(n^2) and not eliminating duplicates*/
void f(char *a, char *b) {

 
  int len_a = strlen(a); 
  int len_b = strlen(b); 
 
  int i, j, k=0; 
  
  char *c = malloc (sizeof(char)*(len_a + len_b)); 
  c[k] = '\0';

  for (i = 0; i < len_a; i++){
    for (j = 0 ; j < len_b; j++){
       if (a[i] == b[j] && a[i] != c[k-1]){
         c[k] = a[i];
         k++; 
       }
    }
  }
  
  c[k] = '\0';

 printf ("The O(n^2) output is: %s\n", c); 

} 

/*This is a hash method taking O(n) and eliminating duplicates */
void f_hash(char *a, char *b){

  int MAX_CHAR = 26; 

  // mark presence of each character as 0
  // in the hash table 'present[]'
  int present[MAX_CHAR];

  int len_a = strlen(a); 
  int len_b = strlen(b); 
  
  int i; 

  char *c = malloc (sizeof(char) * (len_a + len_b)); 
  c[0] = '\0';

  for (i=0; i<MAX_CHAR; i++)
      present[i] = 0;
 
 
  // for each character of a, mark its
  // presence as 1 in 'present[]'
  for (i=0; i<len_a; i++)
      present[a[i] - 'a'] = 1;
   
  // for each character of str2
  for (i=0; i<len_b; i++)
  {
    // if a character of b is also present
    // in a, or previously found in both, then mark its presence as -1
    if (present[b[i] - 'a'] == 1 || present[b[i] - 'a'] == -1)
      present[b[i] - 'a'] = -1;
 
    // else mark its presence as 2
    else
      present[b[i] - 'a'] = 2;
  }
  int j = 0; 
  // save all the common characters in output string c
  for (i=0; i<MAX_CHAR; i++){
    printf("%d, %c\n", present[i], (char)(i+'a'));
    if (present[i] == -1 )
           c[j++]= (char)(i + 'a');
  }
  c[j] = '\0';
  printf ("The O(n) output is: %s\n", c); 


}

int main (){

char * a = "this is one string"; 
char * b = "this is a second string"; 

f(a,b); 
f_hash(a,b); 

}
