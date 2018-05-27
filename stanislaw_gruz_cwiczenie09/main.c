#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <time.h>


unsigned getTerminalWidth();
void gotoxy(unsigned int x, unsigned int y);
void * tFunction(void * tNumber);

int counter = 0;
pthread_mutex_t mutex;


int main(int argc, char * argv[]) {
    srand(time(NULL)); //ustawienie seed'a losowania
    int i;
    const int tNum = 4; //ilosc watkow, ktore zostana utworzone
    pthread_t pThread[tNum];

    system("clear");

    if(pthread_mutex_init(&mutex, NULL) != 0 ) {
        perror("Unable to init mutex!");
        exit(-1);
    }

    for(i=0; i<4; i++) {
        if(pthread_create(&pThread[i], NULL, tFunction, (void *)(intptr_t)i) != 0) {
            perror("Unable to create thread!");
            exit(-1);
        }
        ////// ZARYS ///////
        printf("Watek %d: START\n",i);

    }
    gotoxy(0,5);
    printf("Aktualna wartosc licznika = %d",counter);
    pthread_join(pThread[0], NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}


unsigned getTerminalWidth() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (unsigned) w.ws_col;
}

void gotoxy(unsigned int x, unsigned int y) {
    printf("\033[%d;%dH", y+1, x);
}

void * tFunction(void * tNumber) {
    int tNum = (intptr_t)tNumber,i;
    int termWidth = (int)getTerminalWidth();
    usleep(100000 * (rand() % 6 + 1));


    while(1) {
        //SEKCJA KRYTYCZNA
        /////////////////////////////////////////
        pthread_mutex_lock(&mutex);


        gotoxy(0,tNum);
        printf("\33[2K\r"); //czysci dana linie w terminalu
        fflush(stdout);
        gotoxy(termWidth-27,tNum);
        printf("Watek %d: SEKCJA KRYTYCZNA",tNum);
        fflush(stdout);

        int tempCounter = counter;
        tempCounter++;
        usleep(200000 * (rand() % 7 + 1)); //to musi byc, zeby sekcja krytyczna trwala przez jakis czas
        counter = tempCounter;


        gotoxy(0,tNum);
        printf("\33[2K\r");
        fflush(stdout);
        gotoxy(0,tNum);
        printf("Watek %d: SEKCJA PRYWATNA",tNum);
        fflush(stdout);

        gotoxy(0,5);
        printf("\33[2K\r");
        printf("Aktualna wartosc licznika = %d",counter);

        pthread_mutex_unlock(&mutex);
        ///////////////////////////////////////////

        usleep(120000 + 100000 * (rand() % 15 + 1));

    }
}
