#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include "lib.h"

extern int xA;

int main(int argc, char * argv[]) {


    int i;
    pid_t pid;
    int semid = createSemaphore("powielacz.o", getpid(), 1);
    if(initSemaphore(semid,0) == -1) {
        perror("Unable to init semaphore");
        exit(-1);
    }
    char buff[12];
    sprintf(buff, "%d", semid);
    for(i=0; i<10; i++) {
        if((pid = fork()) == -1) {
            perror("Unable to fork");
            exit(-1);
        } else if(pid == 0) {
            execl("powielacz.o", buff, (char *) NULL);
        } else {

        }

    }
    usleep(2000000);
    printf("Semaphore value in parent process = %d\n", get_value(semid, 0));
    decrementSemaphore(semid);

    removeSemaphore(semid);

    return 0;
}
