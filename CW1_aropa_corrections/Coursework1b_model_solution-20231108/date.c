#include "date.h"		/* so we match the interface signatures */
#include <stdio.h>		/* so we can use sscanf() */
#include <stdlib.h>		/* so we can use malloc()/free() */

struct date {			/* have to define opaque type */
    int day;
    int month;
    int year;
};

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr) {
    int day;
    int month;
    int year;
    Date *d;

    if (sscanf(datestr, "%d/%d/%d", &day, &month, &year) != 3)
        return NULL;		/* incorrectly formatted date string */
    if (day < 1 || day > 31)
        return NULL;		/* incorrectly formatted date string */
    if (month < 1 || month > 12)
        return NULL;		/* incorrectly formatted date string */
    if (year < 1)
        return NULL;		/* incorrectly formatted date string */
    d = (Date *)malloc(sizeof(Date));
    if (d) {
        d->day = day;
        d->month = month;
        d->year = year;
    }
    return d;
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure
 */
Date *date_duplicate(Date *d) {
    Date *ans = (Date *)malloc(sizeof(Date));
    if (ans) {
        ans->day = d->day;
	ans->month = d->month;
	ans->year = d->year;
       /*
        * alternatively, could have done the following single assignment
	*
	* *ans = *d;
	*/
    }
    return ans;
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2) {
/*
 * the following logic should be self-evident
 */
    if (date1->year != date2->year)
        return (date1->year - date2->year);
    if (date1->month != date2->month)
        return (date1->month - date2->month);
    return (date1->day - date2->day);
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d) {
    free(d);
}
