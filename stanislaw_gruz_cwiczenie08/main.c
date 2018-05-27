#include "msg_lib.h"
#include <string.h>
#include <sys/wait.h>
#include <time.h>


#define MAXSIZE 128
#define GNOME_PATH "/usr/bin/gnome-terminal"
#define GNOME_NAME "gnome-terminal"

int main(int argc, char * argv[]) {

    srand(time(NULL));
    pid_t pid;

    //FORK DOTYCZĄCY SERWERA
    switch(pid = fork()) {
    case -1:
        perror("Unable to fork");
        exit(-1);
        break;
    case 0:
        execl("serwer.o", (char *) NULL);
        break;
    }

    //FORKI DOTYCZĄCE KLIENTÓW
    for(int i=0; i<4; i++) {
        switch(pid = fork()) {
        case -1:
            perror("Unable to fork");
            exit(-1);
            break;
        case 0:
            execl(GNOME_PATH, GNOME_NAME, "-e" ,"./klient.o", "klient.o", (char *) NULL);
            break;
        default:
            wait(NULL);
            break;

        }
    }

    wait(NULL);
    return 0;
}
