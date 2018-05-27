
#ifndef _MSG_LIB
#define _MSF_LIB

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSIZE 128

struct msgBuf{
    long mtype;
    long creatorId;
    char mtext[MSGSIZE];
};

int createMsgQueue(char * name, char tChar);
int getMsgQueue(char * name, char tChar);
int removeMsgQueue(int msgid);
int sendMsg(int msgid, struct msgBuf * msg);
int receiveMsg(int msgid, struct msgBuf * msg, long mtype);
int showMsgInfo(int msgid);
int getQueueSize(int msgid);

#endif // _MSG_LIB
