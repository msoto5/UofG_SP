#include<stdio.h>

void manipulateFifthElement(int* x) {
    // do some stuff
    printf("%d\n", x[4]);
    
} // x expires here

int main() {
    int myArray[] = {1,2,3,4,5,6,7,8,9};
    manipulateFifthElement(myArray);
    printf("%d\n", myArray[4]);
    return 0;
}