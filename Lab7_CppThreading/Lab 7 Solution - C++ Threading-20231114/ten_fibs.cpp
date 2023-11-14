#include <stdio.h>
#include <thread>
#include <vector>

// Ten Fibs. A simple example of creating and manipulating an array of C++ threads.
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
  std::vector<std::thread> ts;
  for (int i = 0; i < 10; ++i)
    // Note the capture of the loop index (i)
    ts.emplace_back([i]() {printf("fib(%d) = %d\n", 30+i, fib(30+i));
      });
  for (int i = 0; i < 10; ++i) 
    ts[i].join();
}
