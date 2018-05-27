#ifndef SHM_LIB
#define SHM_LIB

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


struct shmid_ds buf1;

int createSharedMemory(key_t key, int mem_size);
int getSharedMemory(key_t key, int mem_size);
void * getMemoryPointer(int shmid);
void removeSharedMemory(void * p_shmem);
int getShmidDs(int shmid, struct shmid_ds * buf);
void removeRmSegment(int semid, struct shmid_ds * buf);



#endif // SHM_LIB
