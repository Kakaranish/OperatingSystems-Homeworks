#include <stdio.h>
#include <stdlib.h>
#include "procesy.h"

int main(int argc, char * argv[]){

    showProcessInfo();
     printf("======================================\n");
    pid_t child;
    for(int i=0;i<3;i++){
        child = fork();
        if(child == -1){
            perror("Unable to create new process\n");
        }else if(child == 0){

            int ret = execl("file.o", "-l", NULL);

            printf("Ten tekst nie powinien się pojawić :)))");

        }else{

        }
    }

    sleep(3); //sleep zostaje uzyte tutaj, zeby ppid w procesach potomnych zotalo poprawnie wypisane

    return 0;
}
