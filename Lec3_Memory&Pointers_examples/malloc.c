#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr;
    printf("value of ptr (not initialised): %p\n", ptr);
    ptr = (int*) malloc( sizeof(int) );
    printf("value of ptr (initialised): %p\n", ptr);
    
    // do something interesting with p
    *ptr = 12;
    
    free(ptr);
    printf("value of ptr (freed): %p\n", ptr);
    ptr=NULL;
    printf("value of ptr (nulled): %p\n", ptr);

  // stack and heap
  int* p = malloc(sizeof(int));
  int* q = malloc(sizeof(int));
  printf("i: p=%p\t*p=%d\t&p=%p\n", p, *p, &p);
  printf("i: q=%p\t*q=%d\t&q=%p\n", q, *q, &q);

}