#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define ile_procesow 3

void killgroup(pid_t * id, int sig){
    int i;
    for(i=0;i<ile_procesow;i++){
        kill(id[i], sig);
    }
}

pid_t inicjalizujProces(char * arg1, char * arg2){
    pid_t child = fork();
    if(child == -1){
        perror("Nie udalo sie utworzyc procesu potomnego!");
        exit(EXIT_FAILURE);
    }else if(child == 0){
        execl("obsluga.o", "obsluga.o", arg1, arg2, (char *)0);
    }

    return child;
}

int main(int argc, char * argv[]){
    int i;
    pid_t childs[ile_procesow];
    if(argc!=3){
        perror("Nieprawidlowa liczba argumentow");
        return -1;
    }
    for(i=0;i<ile_procesow;i++){
        childs[i] = inicjalizujProces(argv[1],argv[2]);
    }

    printf("Wysylanie sygnalu %d do grupy procesow...\n",atoi(argv[1]));
    sleep(2);
    killgroup(childs, atoi(argv[1]));
    printf("Zakonczono zabijanie procesow potomnych\n");
    return 0;
}
