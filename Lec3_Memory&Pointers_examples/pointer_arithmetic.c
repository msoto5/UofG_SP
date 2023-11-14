#include<stdlib.h>
#include <stdio.h>

int main() {
  int vector[6] = {1, 2, 3, 4, 5, 6};
  int * ptr = vector; // start at the beginning
  while (ptr <= &(vector[5])) {
    printf("%d ", *ptr); // print the element in the array
    ptr++; // go to the next element
  }
  printf("\n");

  int i = 7;
  char c = 'y';
  int * i_ptr = &i;
  char* c_ptr = &c;
  printf("i: i_ptr=%p\ti=%d\n", i_ptr, *i_ptr);
  printf("c: c_ptr=%p\tc=%c\n", c_ptr, *c_ptr);
  i_ptr++; // this adds 4-bytes (sizeof(int)) to the address stored at i_ptr
  c_ptr += 2; // this adds 2-bytes (2 * sizeof(char)) to the address stored at c_ptr
  printf("i: i_ptr=%p\ti=%d\n", i_ptr, *i_ptr);
  printf("c: c_ptr=%p\tc=%c\n", c_ptr, *c_ptr);

  return 0;
}