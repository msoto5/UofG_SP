# Lab 6 Handout - PThread intro
We will be looking at a very simple program that is used as an example in Lecture 6. You can download the code by [clicking here](https://moodle.gla.ac.uk/pluginfile.php/6898478/mod_page/content/10/pthread.c)

1. Download and read the code. The code simply creates a thread using the PThread library. The thread itself does nothing but print a static string.
2. Notice the header files that the program includes. Beside the standard libraries stdio.h and stdlib.h, it includes:
    - pthread.h, used to create and manage threads. This will be explained in this week's lecture.
    - assert.h, used to check given conditions, such as the value of !err in line 15. If the value of the condition is TRUE, the program continues. Otherwise, the program terminates at that point with an error message (e.g. "Assertion failed: " ... details of the error).
3. Compile the file without modifying it.
4. Run the program multiple times, say 10 or 20 times. You should be getting slightly different outputs. Sometimes the thread prints the string message (in line 7) but sometimes it does not. This depends on whether the thread gets to execute before the printf statement on line 16 or after it. If the thread gets scheduled after the printf, then the program reaches its end and terminates normally before the thread gets a chance to run.
5. We can ensure that the created thread always gets scheduled before the end of the program. To do this, uncomment lines 18 and 19. Here we use the join functionality from the pthread library to instruct the program to wait at this point until the thread finishes running.
6. Compile again and run. You should now always see that the thread gets to execute by the output of line 7 always being there.

Notice that a pthread has to have an argument of type void*. In this case, we do not use the pointer and return NULL at the end of the thread. This will also be explained in the lecture.

Try modifying the code to create another thread. Then (optional), have a go at more examples from the lecture. The code is available in a folder at the bottom of the 'Lecture 6' section.