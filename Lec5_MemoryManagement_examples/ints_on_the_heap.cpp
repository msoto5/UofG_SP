#include <iostream>

struct ints_on_the_heap { // This is C++ code and not legal C!
    int * ptr;	// dynamic array of ints
    
    // constructor
    ints_on_the_heap(int size) {
        ptr = (int*)malloc(sizeof(int) * size);
        if (ptr)
            std::cout << "Created!\n";
    }
    
    // destructor
    ~ints_on_the_heap() {
        free(ptr);
        std::cout << "Destroyed!\n";
    }
};
typedef struct ints_on_the_heap ints_on_the_heap;

int main() {
  ints_on_the_heap i(23); // i is on stack; 23 int spaces are allocated on heap
  i.ptr[22] = 42;
} // automatic call to ~ints_on_the_heap will free heap memory
