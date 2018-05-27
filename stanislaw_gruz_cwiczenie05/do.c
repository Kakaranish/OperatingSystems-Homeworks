#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[]){
    srand(time(NULL));

    char * default_path = "tmp/fifo";
    char * fifo_path;
    int file_size;
    FILE * fdo;
    int rfd,i;
    char tempChar;

    if(!(fdo = fopen("res/do.txt", "w"))){
        perror("Nie udalo sie otworzyc pliku");
        return -1;
    }


    if(argc==2){
        fifo_path = malloc(strlen(argv[1] +1) * sizeof(char));
        strcpy(fifo_path, argv[1]);
    }else{
        fifo_path = default_path;
    }

    while(access(fifo_path, F_OK) == -1);

    fflush(stdout);
    rfd = open(fifo_path, O_RDONLY);

    read(rfd, &file_size, sizeof(file_size));

    for(i=0;i<file_size;i++){
        if(read(rfd, &tempChar, sizeof(tempChar))>0){
            usleep((rand() % 3 + 1) * 100000);
            fflush(stdout);
            if(tempChar != '\n')
                printf("Konsument: %c\n",tempChar);
            else
                printf("Konsument: \\n\n");
            fflush(stdout);
            fputc(tempChar,fdo);
        }
    }

    printf("KONIEC POBIERANIA PRZEZ KONSUMENTA\n");

    fclose(fdo);
    close(rfd);

    unlink(fifo_path);

    return 0;
}
