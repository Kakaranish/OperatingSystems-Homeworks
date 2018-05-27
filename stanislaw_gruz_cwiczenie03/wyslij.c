#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <wait.h>

int main(int argc, char * argv[]){

    if(argc != 3){
        printf("Podano nieprawidlowa liczbe argumentow\n");
        return -1;
    }

    pid_t child = fork();
    if(child == -1){
        perror("Tworzenie procesu potomnego zakonczylo sie niepowodzeniem\n");
        return -1;
    }else if(child == 0){
        execl("obsluga.o","obsluga.o",argv[1],argv[2],  (char*)0);
    }else{
        kill(child, atoi(argv[1]));
        printf("Proces potomny został zabity");
    }



    return 0;
}
