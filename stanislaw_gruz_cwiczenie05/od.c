#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char * argv[]){
    srand(time(NULL));
    char * default_path = "tmp/fifo";
    char * fifo_path;
    FILE * fod;
    int file_size = 0;
    int wfd,i;
    char tempChar;

    if(!(fod = fopen("res/od.txt", "r"))){
        perror("Nie udalo sie otworzyc pliku");
        return -1;
    }

    printf("\n");
    fseek(fod, 0, SEEK_END);
    file_size = ftell(fod);
    rewind(fod);

    if(argc==2){
        fifo_path = malloc(strlen(argv[1] +1) * sizeof(char));
        strcpy(fifo_path, argv[1]);
    }else{
        fifo_path = default_path;
        mkfifo(fifo_path, 0664);
    }

    fflush(stdout);

    wfd = open(fifo_path, O_WRONLY);
    write(wfd, &file_size, sizeof(file_size));
    for(i=0;i<file_size;i++){
        tempChar = fgetc(fod);

        usleep(usleep((rand() % 6 + 3) * 100000));
        if(tempChar != '\n')
                printf("Producent: %c\t",tempChar);
            else
                printf("Producent: \\n\t");
        fflush(stdout);

        write(wfd, &tempChar, sizeof(tempChar));
    }

    printf("KONIEC POBIERANIA PRZEZ PRODUCENTA\n");
    fflush(stdout);
    fclose(fod);
    close(wfd);


    return 0;
}
