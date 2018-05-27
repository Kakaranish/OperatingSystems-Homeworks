#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    pid_t childs[2];
    for(int i=0;i<2;i++){
    childs[i] = fork();
        if(childs[i]==-1){
            perror("Nie udalo sie zduplikowac procesu forkiem!");
            return -1;
        }
        else if(childs[i]==0){
            if(i==0){
                if(argc==2) execl("od.o", "od.o", argv[1], NULL);
                else execl("od.o", "od.o", NULL);
            }
            else if(i==1) {
                if(argc==2) execl("do.o", "do.o", argv[1], NULL);
                else execl("do.o", "do.o", NULL);
            }
        }else{

        }
    }
    return 0;
}
