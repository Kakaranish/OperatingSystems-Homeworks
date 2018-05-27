#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

extern const char * const sys_siglist[];

void show_message();
void my_handler(int signal){printf("OBSLUGIWANIE DANEGO SYGNALU...\n");}
void signal_handler(int sig_num, int handling_num);

int main(int argc, char * argv[]){
    int i;
    printf("%d\n",getpid());
    if(argc != 3){
        printf("Nieprawidlowa wywolanie programu!\n");
        show_message();
        return -1;
    }
    int sig_num = atoi(argv[1]);
    int handling_num = atoi(argv[2]);

    signal_handler(sig_num, handling_num);

    //ta petla pogladowo ma pokazac, czy proces zostal zabity czy tez nie
    for(i =0;;i++){
        printf("%d\n",i);
        sleep(1);
    }


    return 0;
}

void show_message(){
    int i;
    printf("Prawidlowe wywolanie programu to: ./nazwa_obiektu a b\n");
    printf("a - numer sygnalu: \n");
    for(i=1;i<=15;i++){
        printf("%d -> %s\t",i, sys_siglist[i]);
        if(i%2 == 0)
            printf("\n");
    }
    printf("\nb - opcja obslugi sygnalu: \n");
    printf("1 -> Domyslnie\t2->Ignorowanie\t3->Zdefiniowane przez uzytkownika\n");
}

void signal_handler(int sig_num, int handling_num){

    if(handling_num == 2){
        if(signal(sig_num, SIG_IGN) == SIG_ERR){
            fprintf(stderr, "Error with %s", sys_siglist[sig_num]);
            perror("");
            exit(EXIT_FAILURE);
        }
    }else if(handling_num == 3){
        if(signal(sig_num, my_handler) == SIG_ERR)
        {
            fprintf(stderr, "Error with %s", sys_siglist[sig_num]);
            perror("");
            exit(EXIT_FAILURE);

        }
    }else{
        if(signal(sig_num, SIG_DFL) == SIG_ERR){
            fprintf(stderr, "Error with %s", sys_siglist[sig_num]);
            perror("");
            exit(EXIT_FAILURE);
        }
    }
}
