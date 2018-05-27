#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "procesy.h"



int main(int argc, char * argv[]){
    pid_t childs[3];

    //sekcja odpowiedzialna za utworzenie procesow potomnych i wypisanie ich pokoleniami
    // M - macierzysty, C - potomek
    /*
    M - pierwsze pokolenie
    C1 - drugie pokolenie
    C2,C3 - trzecie pokolenie
    C4,C5,C6,C7 - czwarte pokolenie

    */
    printf("Proces macierzysty\n");
    showProcessInfo();
    printf("=====================================\n");
    sleep(3);
   
	const int ileForkow = 3;

    for(int i=0;i<ileForkow;i++){
        childs[i] = fork();
        sleep(3);
        if(childs[i] < 0){
            perror("Error while creating new processes\n");
        }else if(childs[i] == 0){
            showProcessInfo();
            sleep(0.0001); //ten delay jest potrzebny, poniewaz w momencie pobrania ppid, proces rodzic zakonczy sie i wyskoczyloby bledne ppid

        }else{

        }
    }

    return 0;
}









