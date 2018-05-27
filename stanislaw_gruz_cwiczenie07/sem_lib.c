#include "sem_lib.h"

int createSemaphore(key_t key, int sem_count){
    return semget(key, sem_count, IPC_CREAT|IPC_EXCL|0600);
}
int getSemaphore(key_t key, int semcnt){
    return semget(key, semcnt, 0666 );
}
int initSemaphore(int semid, int semnum){
    u1.val = 1;
    return semctl(semid, semnum, SETVAL, u1);
}
int setSemaphoreValue(int semid, int semnum, int value){
    u1.val = value;
    return semctl(semid, semnum, SETVAL, u1);
}
int incrementSemaphore(int semid){
    struct sembuf buf = {0,1,0};
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    return semop(semid, &buf, 1);
}
int decrementSemaphore(int semid){
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    return semop(semid, &buf,1);
}
int removeSemaphore(int semid){
    u1.val = 0;
    return semctl(semid, 0, IPC_RMID, u1);
}
int get_value(int semid, int semnum){
    return semctl(semid, semnum, GETVAL, u1);
}
int get_ncnt(int semid, int semnum){
    return semctl(semid, semnum, GETNCNT,u1);
}
int get_zcnt(int semid, int semnum){
    return semctl(semid, semnum, GETZCNT, u1);
}

void showSemaphoreState(int semid, int semnum){
    printf("Semaphore value = %d\n",get_value(semid,semnum));
    fflush(stdout);
    printf("Semaphore ncnt = %d\n",get_ncnt(semid,semnum));
    fflush(stdout);
    printf("Semaphore zcnt = %d\n",get_zcnt(semid,semnum));
    fflush(stdout);
}

