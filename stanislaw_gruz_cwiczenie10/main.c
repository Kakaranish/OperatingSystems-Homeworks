#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>

#define true 1
#define false 0
typedef unsigned short bool;


#define QUEUE_SIZE 10

int counter = 0;
int queueNum[QUEUE_SIZE];
bool choosing[QUEUE_SIZE];

void initArrays();
void * tFunction(void * tNumber);
int getMaxValue();
unsigned getTerminalWidth();
void gotoxy(unsigned int x, unsigned int y);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {

    int i;
    initArrays();

    system("clear");
    pthread_t pThreads[QUEUE_SIZE];

    gotoxy(0,QUEUE_SIZE + 1);
    printf("Licznik = %d",counter);

    for(i=0; i<QUEUE_SIZE; i++) {
        if(pthread_create(&pThreads[i], NULL, tFunction, (void *)(intptr_t) i) != 0) {
            perror("Unable to create thread!");
            exit(-1);
        }
        gotoxy(0,i);
        printf("Watek %d: Sekcja prywatna\n", i);


    }


    pthread_join(pThreads[QUEUE_SIZE-1],NULL);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initArrays() {
    int i;
    for(i=0; i<QUEUE_SIZE; i++) {
        queueNum[i] = 0;
        choosing[i] = false;

    }
}

int getMaxValue() {
    int i, max = queueNum[0];
    for(i=1; i<QUEUE_SIZE; i++) {
        if(queueNum[i] > max)
            max = queueNum[i];
    }
    return max;
}

//(a,b) < (c,d) <=> a < c || (a == c && b < d)

void * tFunction(void * tNumber) {

    int tNum = (intptr_t)tNumber;
    int i, terminalWidth = getTerminalWidth();


    while(1) {

        choosing[tNum] = true;
        queueNum[tNum] = getMaxValue() + 1;
        choosing[tNum] = false;



        //LOCK
        for(i=0; i<QUEUE_SIZE; i++) {
            while(choosing[i]);
            while(queueNum[i] != 0 && (queueNum[i] < queueNum[tNum] || (queueNum[i]==queueNum[tNum] && i < tNum)));
        }

        gotoxy(0,tNum);
        printf("\33[2K\r");
        gotoxy(terminalWidth-28,tNum);
        printf("Watek %d: SEKCJA KRYTYCZNA",tNum);
        fflush(stdout);

        int tempCounter = counter;
        tempCounter++;
        usleep(1000000);
        counter = tempCounter;

        gotoxy(0,QUEUE_SIZE + 1);
        printf("\33[2K\r");
        printf("Licznik = %d",counter);

        gotoxy(0,tNum);
        printf("\33[2K\r");
        printf("Watek %d: Sekcja prywatna",tNum);
        fflush(stdout);
        usleep(1000000);




        queueNum[tNum] = 0; //UNLOCK

    }
}

unsigned getTerminalWidth() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (unsigned) w.ws_col;
}

void gotoxy(unsigned int x, unsigned int y) {
    printf("\033[%d;%dH", y+1, x);
}


