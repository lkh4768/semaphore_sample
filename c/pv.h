#ifndef PA_H
#define PA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SEMPERM	0600 
#define TRUE	1 
#define FALSE	0

typedef union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
} semun;

extern int p(int);
extern int v(int);
extern int initsem(key_t);

#endif
