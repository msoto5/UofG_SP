
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"

struct date
{
    int day;
    int month;
    int year;
};

// Private function prototypes
int date_valid(int day, int month, int year);

/**
 * @brief Checks if a date is valid
 * @param day Day of the date
 * @param month Month of the date
 * @param year Year of the date
 * @return 1 if valid, 0 if not
 */
int date_valid(int day, int month, int year)
{
    /* Enough to check that 0<day<32, 0<month<13, year>0.*/
    if (year < 0)
        return 0;

    if (month < 1 || month > 12)
        return 0;

    if (day < 1 || day > 31)
        return 0;

    return 1;
}

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr)
{
    Date *d = NULL;
    char *s1, *s2, *datestr2;
    int day, month, year;

    // printf("%s\n", datestr);
    /* Error control */
    if (!datestr)
        return NULL;

    datestr2 = strdup(datestr);
    if (!datestr2)
        return NULL;

    /* Get date, month and year */
    s2 = strrchr(datestr2, '/');
    if (!s2)
        return NULL;

    *s2 = '\0';

    s1 = strrchr(datestr2, '/');
    if (!s1)
        return NULL;

    *s1 = '\0';

    // printf("\nDate create CHECK:\n");
    // printf("s1 -> %s\t s2 -> %s\n", s1, s2);

    day = atoi(datestr2);
    month = atoi(s1 + 1);
    year = atoi(s2 + 1);

    // printf("day -> %d\t month -> %d\t year -> %d\n", day, month, year);

    /* Check if given input date is valid */
    if (!date_valid(day, month, year))
    {
        return NULL;
    }

    /* Create Date structure */
    d = (Date *)malloc(sizeof(Date));
    if (!d)
    {
        return NULL;
    }
    d->day = day;
    d->month = month;
    d->year = year;

    free(datestr2);

    return d;
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d)
{
    Date *d2 = NULL;

    /* Error Control */
    if (!d)
        return NULL;

    d2 = (Date *)malloc(sizeof(Date));
    if (!d2)
        return NULL;

    d2->day = d->day;
    d2->month = d->month;
    d2->year = d->year;

    return NULL;
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2)
{
    /* Error Control */
    if (!date1 || !date2)
        return 0;

    // Compare year
    if (date1->year < date2->year)
        return -1;
    else if (date1->year > date2->year)
        return 1;

    // Compare month
    if (date1->month < date2->month)
        return -1;
    else if (date1->month < date2->month)
        return 1;

    // Compare day
    if (date1->day < date2->day)
        return -1;
    else if (date1->day > date2->day)
        return 1;

    return 0;
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d)
{
    if (d)
    {
        free(d);
    }

    return;
}