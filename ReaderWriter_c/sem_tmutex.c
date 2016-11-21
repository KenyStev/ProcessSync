#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t db;
int readercount=0;
pthread_t reader1,reader2,writer1,writer2;
void *reader(void *);
void *writer(void *);

int main()
{
	sem_init(&mutex,0,1);
	sem_init(&db,0,1);
	// while(1)
	// {
		pthread_create(&reader1,NULL,reader,"1");
		pthread_create(&reader2,NULL,reader,"2");
		pthread_create(&writer1,NULL,writer,"1");
		pthread_create(&writer2,NULL,writer,"2");
	// }
	// return 0;
	pthread_exit(NULL);
}

void *reader(void *p)
{
	while(1)
	{
		printf("prevoius value %d\n",mutex);
		sem_wait(&mutex);
		printf("Mutex acquired by reader %d\n",mutex);
		readercount++;
		if(readercount==1) sem_wait(&db);
		sem_post(&mutex);
		printf("Mutex returned by reader %d\n",mutex);
		printf("Reader %s is Reading\n",p);
		// sleep(1);
		sem_wait(&mutex);
		printf("Reader %s Completed Reading\n",p);
		readercount--;
		if(readercount==0) sem_post(&db);
		sem_post(&mutex);
	}
}

void *writer(void *p)
{
	while(1)
	{
		printf("Writer is Waiting\n");
		sem_wait(&db);
		printf("~> Writer %s is writing\n",p);
		sem_post(&db);
		// sleep(1);
	}
}