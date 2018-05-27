#include "msg_lib.h"


int createMsgQueue(char * name, char tChar){
    key_t key = ftok(name, tChar);
    if(key==-1){
        perror("Unable to create key!");
        exit(-1);
    }
    //printf("Created %d",key);
    return msgget(key, IPC_CREAT | IPC_EXCL | 0666);
}

int getMsgQueue(char * name, char tChar){
    key_t key = ftok(name, tChar);
    if(key == -1){
        perror("Unable to create key!");
        exit(-1);
    }
    return msgget(key, 0666);
}


int removeMsgQueue(int msgid){
    return msgctl(msgid, IPC_RMID, NULL);
}

int sendMsg(int msgid, struct  msgBuf * msg){
    msgsnd(msgid, msg, MSGSIZE, 0);
}

int receiveMsg(int msgid, struct msgBuf * msg, long mtype){
    return msgrcv(msgid, msg, MSGSIZE, mtype, 0);
}

int showMsgInfo(int msgid){
    struct msqid_ds tDs;
    if(msgctl(msgid, IPC_STAT, &tDs) < 0)
        return -1;


    printf("PID of last msgsnd = %d\n",tDs.msg_lspid);
    printf("PID of last msgrcv = %d\n",tDs.msg_lrpid);
    printf("Amount of messages in the queue = %d\n",tDs.msg_qnum);
    printf("Amount of bytes in queue = %d\n", tDs.__msg_cbytes);



    return 1;
}

int getQueueSize(int msgid){
    struct msqid_ds buf;
    if(msgctl(msgid, IPC_STAT, &buf) < 0){
        perror("Unable to get IPC_STAT!\n");
        exit(-1);
    }
    return buf.msg_qnum;
}
