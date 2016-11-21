#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "../utils.c"
#include "../sem.c"

// for sleep
#include <unistd.h>

#define BUFF_SIZE   5           /* total number of slots */
#define NP          3           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */

typedef struct
{
  int buf[BUFF_SIZE];   /* data_buffer var */
  int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
  int out;              /* buf[out%BUFF_SIZE] is the first full slot */
  Semaphore *full;           /* keep track of the number of full spots */
  Semaphore *empty;          /* keep track of the number of empty spots */

  // use correct type here
  pthread_mutex_t mutex;          /* enforce mutual exclusion to data_buffer data */
} mem_buf;

mem_buf data_buffer;


void *Writer(void *arg)
{
  int item=0, index;

  index = (int)arg;


  while(1)
  {

    /* Produce item */
    item++;

    /* If there are no empty slots, wait */
    semaphore_wait(data_buffer.empty);
    /* If another thread uses the buffer, wait */
    pthread_mutex_lock(&data_buffer.mutex);
    data_buffer.buf[data_buffer.in] = item;
    data_buffer.in = (data_buffer.in+1)%BUFF_SIZE;
    printf("%d Writer, writting %d\n", index, item);
    fflush(stdout);
    /* Release the buffer */
    pthread_mutex_unlock(&data_buffer.mutex);
    /* Increment the number of full slots */
    semaphore_signal(data_buffer.full);

    sleep(1);
  }
  return NULL;
}

void *Reader(void *arg)
{
  int item=0, index;

  index = (int)arg;
  while(1)
  {
    semaphore_wait(data_buffer.full);
    pthread_mutex_lock(&data_buffer.mutex);
    item++;
    item=data_buffer.buf[data_buffer.out];
    data_buffer.out = (data_buffer.out+1)%BUFF_SIZE;
    printf("%d Reader, Consuming  %d\n", index, item);
    fflush(stdout);
    /* Release the buffer */
    pthread_mutex_unlock(&data_buffer.mutex);
    /* Increment the number of full slots */
    semaphore_signal(data_buffer.empty);

    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t idP, idC;
  int index;

  data_buffer.full = make_semaphore(0);
  data_buffer.empty = make_semaphore(BUFF_SIZE);
  pthread_mutex_init(&data_buffer.mutex, NULL);
  for (index = 0; index < NP; index++)
  {
    /* Create a new producer */
    pthread_create(&idP, NULL, Writer, (void*)index);
  }
  /*create a new Reader*/
  for(index=0; index<NC; index++)
  {
    pthread_create(&idC, NULL, Reader, (void*)index);
  }

  // while(1);

  pthread_exit(NULL);
}