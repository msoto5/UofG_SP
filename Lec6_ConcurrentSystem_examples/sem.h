/*
  * sem.h: simple semaphore interface
  */

#ifndef _SEM_H_
#define _SEM_H_

typedef void *sem_t;	/* the actual type is private, defined in sem.c */

#define SEM_MAX_VALUE 1147483648

/* create a semaphore, assiging its initial value, noting its maximum value
  * returns the semaphore, or NULL if failure */
sem_t sem_create(unsigned int initial, unsigned int maximum);

/* destroy the semaphore; return 1 if successful, 0 otherwise */
int sem_destroy (sem_t s);

/* signal the semaphore; returns 1 if successful, 0 otherwise */
int sem_signal(sem_t s);

/* wait for the semaphore; returns 1 if successful, 0 otherwise */
int sem_wait (sem_t s);

#endif	/* _SEM_H_ */
