#include "msg_lib.h"
#include <string.h>
#include <time.h>
#define MAXSIZE 128


char * randString(int size){

     char tekst[size];
     int i;
     for(i=0;i<size;i++){
        tekst[i] = rand() % 26 + 'a';
     }

     char * s = malloc(size+1);
     strncpy(s, tekst, size);
     return s;
}

int main(int argc, char * argv[]){

    srand(time(NULL) + getpid()); //ustawienia seed'a
    struct msgBuf msg;

    key_t key = ftok(".",'x');
    int msgid = getMsgQueue(".",'x');

    char * sText = randString(rand() % 10 + 20);

    strncpy(msg.mtext, sText, strlen(sText));

    msg.mtype = 1;
    msg.creatorId = getpid();

    sendMsg(msgid, &msg);
    receiveMsg(msgid, &msg, getpid());


    printf("Wiadomosc otrzymana od serwera(po operacji): %s\n", msg.mtext);

    sleep(4);



    return 0;
}
