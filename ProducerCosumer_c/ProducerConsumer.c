#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "../utils.c"
#include "../sem.c"

#define BUFF_SIZE   5           /* total number of slots */
#define NP          3           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */

typedef struct
{
  int table[BUFF_SIZE];   /* table_data var */
  int in;               /* table[in%BUFF_SIZE] is the first empty slot */
  int out;              /* table[out%BUFF_SIZE] is the first full slot */
  Semaphore *full;           /* keep track of the number of full spots */
  Semaphore *empty;          /* keep track of the number of empty spots */

  // use correct type here
  pthread_mutex_t mutex;          /* enforce mutual exclusion to table_data data */
} queue;

queue table_data;


void *Producer(void *arg)
{
  int item=0, index;

  index = (int)arg;


  while(1)
  {

    /* Produce item */
    item++;

    /* If there are no empty slots, wait */
    semaphore_wait(table_data.empty);
    /* If another thread uses the tablefer, wait */
    pthread_mutex_lock(&table_data.mutex);
    table_data.table[table_data.in] = item;
    table_data.in = (table_data.in+1)%BUFF_SIZE;
    printf("%d Producer, Producing %d\n", index, item);
    fflush(stdout);
    /* Release the tablefer */
    pthread_mutex_unlock(&table_data.mutex);
    /* Increment the number of full slots */
    semaphore_signal(table_data.full);

    sleep(1);
  }
  return NULL;
}

void *Consumer(void *arg)
{
  int item=0, index;

  index = (int)arg;
  while(1)
  {
    semaphore_wait(table_data.full);
    pthread_mutex_lock(&table_data.mutex);
    item++;
    item=table_data.table[table_data.out];
    table_data.out = (table_data.out+1)%BUFF_SIZE;
    printf("%d Consumer, Consuming  %d\n", index, item);
    fflush(stdout);
    /* Release the tablefer */
    pthread_mutex_unlock(&table_data.mutex);
    /* Increment the number of full slots */
    semaphore_signal(table_data.empty);

    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t idP, idC;
  int index;

  table_data.full = make_semaphore(0);
  table_data.empty = make_semaphore(BUFF_SIZE);
  pthread_mutex_init(&table_data.mutex, NULL);
  for (index = 0; index < NP; index++)
  {
    /* Create a new producer */
    pthread_create(&idP, NULL, Producer, (void*)index);
  }
  /*create a new Consumer*/
  for(index=0; index<NC; index++)
  {
    pthread_create(&idC, NULL, Consumer, (void*)index);
  }

  // while(1);

  pthread_exit(NULL);
}