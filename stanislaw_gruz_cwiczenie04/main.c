#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main(int argc, char * argv[]){

    srand((time(NULL)));
    int i;
    int fd[2];
    pid_t child;
    char * buffer;
    int bufferSize;
    char * read_buffer;

    pipe(fd);
    if((child = fork()) == -1){
        perror("Nie mozna utworzyc procesu potomnego\n");
        return -1;
    }else if(child == 0){

        FILE * fod;
        if(!(fod = fopen("od.txt", "r"))){
        printf("Nie udalo sie otworzyc pliku od.txt\n");
        return -1;
        }

        fseek(fod, 0, SEEK_END);
        bufferSize = ftell(fod);

        close(fd[0]);
        write(fd[1],&bufferSize, sizeof(bufferSize));

        buffer = malloc((bufferSize) * sizeof(*buffer));
        rewind(fod);

        printf("======PRZESYLANIE DO PRODUCENTA===========\n");
        char tempChar;
        for(i=0;i<bufferSize;i++){
            if(i==bufferSize-1){
                buffer[i] = '\0';
                break;
            }
            tempChar = (char)(fgetc(fod));
            buffer[i] = tempChar;
            printf("%c",buffer[i]);
            fflush(stdout);
            usleep((rand() % 20 +1) * 10000 );
        }
        fclose(fod);
        printf("\n=========KONIEC PRZESYLANIA PLIKU==========\n");
        printf("\n\n");

        for(i=0;i<bufferSize;i++){
            close(fd[0]);
            write(fd[1], &buffer[i],sizeof(char));
        }

        return 0;

    }else{

        FILE * fdo;
        if(!(fdo = fopen("do.txt", "w"))){
        printf("Nie udalo sie otworzyc pliku do.txt\n");
        return -1;
        }

        close(fd[1]);
        read(fd[0], &bufferSize, sizeof(bufferSize)); //poprzez pipeling pobieram rozmiar pliku

        char tempC;
        wait(NULL);
        printf("====PRZESYLANIE POTOKIEM DO KONSUMENTA====\n");

        for(i=0;i<bufferSize-1;i++){
            close(fd[1]);
            read(fd[0], &tempC, sizeof(tempC));
            printf("%c",tempC);
            fflush(stdout);
            usleep((rand() % 20 +1) * 10000 );
            fflush(fdo);
            fputc(tempC, fdo);
        }

        fclose(fdo);

        printf("\n====KONIEC PRZESYLU DO KONSUMENTA========\n");
        printf("Zakonczono zapis do pliku!\n");
    }

    return 0;
}

