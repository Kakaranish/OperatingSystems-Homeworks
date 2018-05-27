#ifndef _LIB
#define _LIB

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//na wszelki wypadek, gdyby unia senum nie byla zdefiniowana
#ifdef _SEM_SEMUN_UNDEFINED
union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfor * __buf;
} u1;
#endif // _SEM_SEMUN_UNDEFINED

static struct sembuf buf;

int createSemaphore(key_t key, int sem_count);
int getSemaphore(key_t key, int semcnt);
int initSemaphore(int semid, int semnum);
int setSemaphoreValue(int semid, int semnum, int value);
int incrementSemaphore(int semid);
int decrementSemaphore(int semid);
int removeSemaphore(int semid);

int get_value(int semid, int semnum);
int get_ncnt(int semid, int semnum);
int get_zcnt(int semid, int semnum);
void showSemaphoreState(int semid, int semnum);
#endif // _LIB
