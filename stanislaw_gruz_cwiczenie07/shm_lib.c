#include "shm_lib.h"


int createSharedMemory(key_t key, int shm_size){
    return shmget(key, shm_size, IPC_CREAT | 0666);
}
int getSharedMemory(key_t key, int shm_size){
    return shmget(key, shm_size,0666);
}
void * getMemoryPointer(int shmid){
    return shmat(shmid, NULL, 0);
}
void removeSharedMemory(void * p_shmem){
    shmdt(p_shmem);
}

void removeRmSegment(int shmid, struct shmid_ds * buf){
    shmctl(shmid, IPC_RMID, buf);
}

int getShmidDs(int shmid, struct shmid_ds * buf ){
    return shmctl(shmid, IPC_STAT, buf);
}
