#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<unistd.h>
#include "lib.h"

int main(int argc, char * argv[]) {

    if(argc != 1){
        printf("Inadequate number of arguments\n");
        fflush(stdout);
        exit(-1);
    }
    int semid = atoi(argv[0]);

    if(decrementSemaphore(semid)==-1) {
        perror("Unable to decrement semaphore");
        fflush(stdout);
        exit(-1);
    }

    ///////////////////////////////////////////////////////////////////////////////
    printf("Semaphore before decrementation SEM_VALUE = %d\n", get_value(semid,0)+1); //skoro funkcja decrementSemaphore nie wyrzucila bledu, to znaczy, ze z pewnoscia dekrementowalismy semafor

    fflush(stdout);

    printf("Decrementation...\n");
    fflush(stdout);

    printf("Critical section\n");
    printf("Number of processes waiting for resource = %d\n", get_ncnt(semid,0));
    fflush(stdout);
    showSemaphoreState(semid, 0);
    printf("Incrementation...End of critical section\n");
    fflush(stdout);
    usleep(30000);

    //////////////////////////////////////////////////////////////////////////
    incrementSemaphore(semid);



    printf("END OF CHILD PROCESS\n");
    fflush(stdout);
    printf("------------------------------------------------\n\n\n");
    fflush(stdout);


    return 0;
}
