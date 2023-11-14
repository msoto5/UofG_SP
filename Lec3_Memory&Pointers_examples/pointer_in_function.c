#include <stdlib.h>
// This file is NOT syntactically correct, so it will not compile (figure out why ;) )
// It is used solely for illustrating the difference between correct and wrong uses of passing pointers back and forth between main and helper functions.

struct date * date_create_correct (char * c) {
	struct date * d = malloc();
	return d;
}

int * date_create_wrong(struct date *d, char *c ) {
	int i = 5; 
	d = malloc();
	return &i;
}

int main () {
	struct date *d; 
	int * i = date_create_wrong( d, "string");
	struct date *b; 
	b = date_create_right ("string");
}