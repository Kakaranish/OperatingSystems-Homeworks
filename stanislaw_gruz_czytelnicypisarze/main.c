#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//ZMIENNE GLOBALNE
unsigned reader_counter = 0;
pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER, wait_mutex = PTHREAD_MUTEX_INITIALIZER, output_mutex = PTHREAD_MUTEX_INITIALIZER;

//DEKLARACJE FUNKCJI
unsigned getTerminalWidth();
void gotoxy(unsigned int x, unsigned int y);
void clear();
void * reader(void * arg);
void * writer(void * arg);
void sleepRand();


int main(int argc, char * argv[]){
  srand(time(NULL));
  system("clear");
  int i;
  unsigned t_num = rand() % 10 + 6;
  pthread_t * thread = malloc(sizeof(pthread_t) * t_num);

  for(i=0;i<t_num;i++){
    int x = rand() % 2 + 1;
    pthread_mutex_lock(&output_mutex);
    if(x%2==0){
      if(pthread_create(&thread[i], NULL, reader, (void *)(intptr_t)(i)) != 0){
        perror("Creating reader's thread failed");
        exit(-1);
      }
      gotoxy(0, i);
      printf("Czytelnik");
    }else{
      if(pthread_create(&thread[i], NULL, writer, (void *)(intptr_t)(i)) != 0){
        perror("Creating writer's thread failed ");
        exit(-1);
      }
      gotoxy(0, i);
      printf("Pisarz");
    }
    pthread_mutex_unlock(&output_mutex);
  }
  pthread_join(thread[0], NULL);


  free(thread);
  pthread_mutex_destroy(&wait_mutex);
  pthread_mutex_destroy(&r_mutex);
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clear(){
  printf("\33[2K\r");
}
/////////////////////////////////////////////
unsigned getTerminalWidth() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (unsigned) w.ws_col;
}
/////////////////////////////////////////////
void gotoxy(unsigned int x, unsigned int y) {
    printf("\033[%d;%dH", y+1, x);
}
/////////////////////////////////////////////
void * reader(void * arg){
  int thread_num = (intptr_t)arg;
  unsigned terminal_width = getTerminalWidth();

  while(1){

    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(0,thread_num);
    printf("Czytelnik poza poczekalnia");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);


    ////////////////////////////////////////////////////////////////
    /// PROBA WEJSCIA DO POCZEKALNI
    ///////////////////////////////////////////////////////////////
    pthread_mutex_lock(&wait_mutex);
    pthread_mutex_unlock(&wait_mutex);

    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(0,thread_num);
    printf("Czytelnik w poczekalni");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);
    //jesli przejdzie przez te dwie linijki kodu to znaczy, ze znajduje sie w poczekalni

    pthread_mutex_lock(&r_mutex); //sekcja krytyczna czytelnika
    reader_counter++;

    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(terminal_width-40,thread_num);
    printf("Czytelnik CZYTA");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);
    pthread_mutex_unlock(&r_mutex);
    sleepRand();


    pthread_mutex_lock(&r_mutex);
    reader_counter--;
    pthread_mutex_unlock(&r_mutex);
  }
}

/////////////////////////////////////////////
void * writer(void * arg){
  int thread_num = (intptr_t) arg;
  unsigned terminal_width = getTerminalWidth();

  while(1){
    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(0,thread_num);
    printf("Pisarz czeka na poczekalnie");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);
    sleepRand();
    //////////////////////////////
    // SEKCJA KRYTYCZNA
    //////////////////////////////
    pthread_mutex_lock(&wait_mutex);


    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(0,thread_num);
    printf("Pisarz BLOKUJE POCZEKALNIE");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);



    while(reader_counter>0);

    sleepRand();
    pthread_mutex_lock(&output_mutex);
    gotoxy(0,thread_num);
    clear();
    gotoxy(terminal_width - 40,thread_num);
    printf("Pisarz pisze");
    fflush(stdout);
    pthread_mutex_unlock(&output_mutex);
    sleepRand();
    pthread_mutex_unlock(&wait_mutex);
  }

}
//////////////////////////////////////////////
void sleepRand(){
  int x = rand() % 12 + 6;
  usleep(x * 100000);
}
