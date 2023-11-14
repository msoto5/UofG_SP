#include <stdio.h>

// Three Fibs. A simple C++ program
// Phil Trinder, November 2020 

int fib(int x, int x1, int x2) {
    if (x == 0) {
        return x2;
    } else {
        return fib(x - 1, x1 + x2, x1);
    }
}

int fib(int x) {
    return fib(x, 0, 1);
}

int main() {
  printf("fib(40) = %d\n", fib(40));  
  printf("fib(41) = %d\n", fib(41));  
  printf("fib(42) = %d\n", fib(42));  
}
