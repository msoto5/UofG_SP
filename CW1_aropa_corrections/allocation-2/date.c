#include <stdlib.h>		
#include "date.h"		 
#include <stdio.h>		


// Define the structure 'date' with three integer members  day, month, and year
struct date {
    int theDay;
    int theMonth;
    int theYear;
};

// This function is create a Date object 

Date *date_create(char *datestr) {
    int theDay;
    int theMonth;
    int theYear;

    // Pointer for the new date object
    Date *newDate;

    //Here we are trying to check if new String fits into Date object stracture day,month,Year

    if (sscanf(datestr, "%d/%d/%d", &theDay, &theMonth, &theYear) != 3)
        return NULL;        

    // checking if the year is valid and it is above 1
    if (theYear < 1)
        return NULL;  

    // checking if the day is valid and it is above 1
    if (theDay < 1)
        return NULL;     

    // checking if the month is valid and it is above 1
    if (theMonth < 1)
        return NULL;     
                

    // checking if the day is valid and it is not above the maxxmuim days in the month which is  31
    if ( theDay > 31)
        return NULL;   
        
    // checking if the month is valid and if it is above 12 it will return NULL
           
    if (theMonth > 12)
        return NULL;     


// Allocate memory for the new date object

    newDate = malloc(sizeof(Date));


// If allocation is successful, set the date object's properties
    if (newDate) {
        newDate->theDay = theDay;
        newDate->theMonth = theMonth;
        newDate->theYear = theYear;
    }
    return newDate;
}


// Function to create a duplicate of a given date object
Date *date_duplicate(Date *d) {


    if (d == NULL) {
        return NULL;  
    }

   // Allocate memory for the duplicate date object
    Date *duplicate = (Date *)malloc(sizeof(Date));
    
    
    // If allocation is successful, copy the date information
    if (duplicate != NULL) {
        
        duplicate->theYear = d->theYear;   
        duplicate->theMonth = d->theMonth; 
        duplicate->theDay = d->theDay;
    }

    // Return the pointer to the duplicate date object
    return duplicate;
}


// Function to compare two dates

int date_compare(Date *date1, Date *date2) {
        // If either date is NULL, return 0 indicating no comparison was made
    if (date1 == NULL || date2 == NULL) {
        return 0;  
    }

    // Compare years, then months, then days and return -1, 1, or 0 accordingly

    // -1 means that the date2 is greater than date1 
    // 1 means that the date1  is greater than date2 
    // 0 means that the date2 and date1 is equal 

    if (date1->theYear < date2->theYear) {
        return -1;
    } else if (date1->theYear > date2->theYear) {
        return 1;
    }
    
    if (date1->theMonth < date2->theMonth) {
        return -1;
    } else if (date1->theMonth > date2->theMonth) {
        return 1;
    }
    
    if (date1->theDay < date2->theDay) {
        return -1;
    } else if (date1->theDay > date2->theDay) {
        return 1;
    }
    
    return 0;  
}

// Function to deallocate a date object
void date_destroy(Date *d) {
    free(d);
}








