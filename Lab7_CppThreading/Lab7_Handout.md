# Lab 7 Handout - C++ Threading

The purpose of this lab is to get you familiar with C++ and C++ threaded programming. Doing so will greatly assist you with Coursework 2.

## Part 0 - Set Profile to use a recent Clang

To set your profile to use a recent version of Clang on the servers, run the following in the command shell on one of the stlinux servers (not ssh or sibu):

% source /usr/local/bin/clang9.setup

## Part 1 - Creating & Waiting for Threads

    Sequential Fibonacci: Write a C++ program three_fibs.cpp that prints out the values of Fibonacci(40), Fibonacci(41), and Fibonacci(42). You can write your own Fibonacci function, or use


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

    Threaded Fibonacci: Refactor your program into three_fibs_threaded.cpp to create two threads, one to print out Fibonacci(40), and the other to print Fibonacci(41), while main() prints Fibonacci(42). The cppthreads_hello_world.cpp program in the Lecture 7 code examples is a good model for the threading.
    Performance Analysis: Use the time utility to record the (real) execution time for at least three runs of three_fibs and three_fibs_threaded, e.g. time ./three_fibs  Is there a difference in the runtimes? Explain why.

## Part 2 - Creating an Array of Threads, Capturing Values

    Array of Threads: Write a C++ program ten_fibs.cpp that creates an std::vector of threads, and uses them to compute Fibonacci(30), Fibonacci(31), ..., Fibonacci(39). Think carefully about the values captured by, and passed as parameters to, the thread.
    Output: Is your output correct? How easy is it to understand and check? Can you make it more comprehensible?