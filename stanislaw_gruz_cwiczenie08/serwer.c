#include "msg_lib.h"
#include <ctype.h>


#define MAXSIZE 128



void msgToupper(struct msgBuf * msg) {
    int i;
    for(i=0;; i++) {
        if(msg->mtext[i] != '\0') {
            msg->mtext[i]= toupper(msg->mtext[i]);
        } else
            break;
    }
}



int main(int argc, char * argv[]) {

    struct msqid_ds buf;
    struct msgBuf sMsg;
    int msgid = createMsgQueue(".", 'x');
    int qSize;


    usleep(500000);


    while(1) {
        qSize = getQueueSize(msgid);
        if(qSize == 0)
            break;

        receiveMsg(msgid, &sMsg, 1);

        printf("Otrzymana wiadomosc od klienta: %s\n", sMsg.mtext);
        fflush(stdout);

        msgToupper(&sMsg);
        sMsg.mtype = sMsg.creatorId;

        sendMsg(msgid, &sMsg);

        usleep(200000);


    }
    printf("\n\nKONIEC PRACY SERWERA!");
    removeMsgQueue(msgid);
}
