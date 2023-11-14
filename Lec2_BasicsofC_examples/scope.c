#include <stdio.h>

int foo(int i) {
    int j = i;
    {
        int j = i + 2;
        printf("%d\n", j);
    }
    return j + 1;
}

int main() {
  int i = 5;
  {
    int j = foo(i);
    printf("%d\n", j);
  }
}