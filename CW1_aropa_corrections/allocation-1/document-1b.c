#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "date.h"

// struct stores integers for each date field
struct date {
    int day;
    int month;
    int year;
};

// checks whether the date is a leap year or not
// amends days of February based on the check
bool isLeapYear(int year) {
    bool leapYear;

    if (year % 400 == 0) {
        leapYear = true;
    } else if (year % 100 == 0) {
        leapYear = false;
    } else if (year % 4 == 0) {
        leapYear = true;
    } else {
        leapYear = false;
    }

    return leapYear;
}

Date *date_create(char *datestr) {
    // null pointers to prevent any errors

    if (!datestr) {
        return NULL;
    }

    Date *newDate = malloc(sizeof(Date));

    if (!newDate) {
        return NULL;
    }

    // using sscanf() to read and format the date into the fields required
    // if condition checks whether there is more than three characters of the date field or not
    if (sscanf(datestr, "%2d/%2d/%4d", &newDate->day, &newDate->month, &newDate->year) != 3) {
        free(newDate);
        return NULL;
    }

    bool leapYear = isLeapYear(newDate->year);
    int febDayNum = 29;

    // changes leap year day count to dynamically change for the switch case
    if (!leapYear) {
        febDayNum = 28;
    }


    switch (newDate->month) {
        // cases represent months and conditions show their day count depending on the months
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (newDate->day < 1 || newDate->day > 31) {
                free(newDate);
                printf("Invalid day entered");
                return NULL;
            }
            break;


        case 4:
        case 6:
        case 9:
        case 11:
            if (newDate->day < 1 || newDate->day > 30) {
                free(newDate);
                printf("Invalid day entered \n");
                return NULL;
            }
            break;

        case 2:
            if (newDate->day < 1 || newDate->day > febDayNum) {
                free(newDate);
                printf("Invalid day entered \n");
                return NULL;
            }
            break;

        default:
            free(newDate);
            printf("Invalid month entered \n");
            return NULL;

    }
    return newDate;
}

Date *date_duplicate(Date *d) {
    if (!d) {
        return NULL;
    }

    Date *dateCpy = malloc(sizeof(Date));

    if (!dateCpy) {
        return NULL;
    }

    // initialises the dateCpy of type Date to duplicate the contents of the pointer d in the parameter
    dateCpy->day = d->day;
    dateCpy->year = d->year;
    dateCpy->month = d->month;

    return dateCpy;
}

int date_compare(Date *date1, Date *date2) {
    if (!date1 || !date2) {
        return 0;
    }

    // compares the dates linearly based on the stackoverflow reference I saw: https://stackoverflow.com/questions/5283120/date-comparison-to-find-which-is-bigger-in-c
    if (date1->year < date2->year) {
        return -1;
    } else if (date1->year > date2->year) {
        return 1;
    }

    if (date1->year == date2->year) {
        if (date1->month < date2->month) {
            return -1;
        } else if (date1->month > date2->month) {
            return 1;
        } else if (date1->day < date2->day) {
            return -1;
        } else if (date1->day > date2->day) {
            return 1;
        }
    }

    return 0;
}

void date_destroy(Date *d) {
    // checks if the Date struct pointer variable d exists
    // then frees it from the heap
    if (d) {
        free(d);
    }
}