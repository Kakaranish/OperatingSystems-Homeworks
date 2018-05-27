#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sem_lib.h"
#include "shm_lib.h"

int main(int argc, char * argv[]) {
    srand(time(NULL));

    //VARIABLES
    int i;
    pid_t pid;
    char * shmem;
    int const shm_size = 10; //pamiec dzielona bedzie miala rozmiar 10 bajtow
    key_t shm_key = ftok(".",'x'); //id pamieci dzielonej
    key_t sem_key = ftok(".", 'a'); //id semafora
    int shmid = createSharedMemory(shm_key, shm_size);
    int delay = 200000;


    //CREATING AND INITIALIZATION SEMAPHORE
    int semid;
    if((semid = createSemaphore(sem_key, 1))==-1) {
        perror("Unable to create semaphore");
        exit(-1);
    }
    if(initSemaphore(semid,0) == -1) {
        perror("Unable to init semaphore");
        exit(-1);
    }


    //CREATING SHARED MEMORY
    if(shmid == -1) {
        perror("Unable to create shared memory");
        exit(-1);
    }
    if((shmem = getMemoryPointer(shmid)) == (char *)-1) {
        perror("Unable to attach memory segment to data space!");
        exit(-1);
    }

    ///////////////////////////////////////////////////////
    // FORK
    ///////////////////////////////////////////////////////

    if((pid = fork()) == -1) {
        perror("Unable to fork()");
        exit(-1);
    } else if(pid == 0) {

        char *p_shmem = shmem;
        FILE * fod;
        if(!(fod = fopen("od.txt", "r"))) {
            perror("Unable to open od.txt file");
            exit(-1);
        }

        char tempChar;
        while(tempChar != EOF) {

            p_shmem = shmem;
            ////////////////////////////////////////////
            //CRITICAL SECTION
            ////////////////////////////////////////////
            decrementSemaphore(semid);

            for(i=0; i<shm_size; i++) {

                tempChar = fgetc(fod);
                *p_shmem = tempChar;

                if(tempChar == EOF)
                    break;
                p_shmem++;
            }

            incrementSemaphore(semid);
            // END OF CRITICAL SECTION

            usleep(delay+100);

        }
        fclose(fod);


    } else {

        FILE * fdo;
        if(!(fdo = fopen("do.txt", "w"))) {
            perror("Unable to open/create do.txt");
            exit(-1);
        }
        char * p_shmem, tempChar;


        usleep(delay);
        while(tempChar != EOF) {

            p_shmem = shmem;
            ////////////////////////////////////////////
            //CRITICAL SECTION
            ////////////////////////////////////////////

            decrementSemaphore(semid);

            for(i=0; i<shm_size; i++) {
                tempChar = *p_shmem;
                if(tempChar == EOF)
                    break;
                printf("%c",tempChar);
                fputc(tempChar, fdo);

                p_shmem++;
            }

            incrementSemaphore(semid);
            // END OF CRITICAL SECTION
            usleep(delay);

        }

        fclose(fdo);
        removeSemaphore(semid);
        removeSharedMemory(shmem);
    }


    return 0;
}
