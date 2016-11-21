#include "ProducerConsumer.h"

ProducerConsumer::ProducerConsumer()
{
    in=0;
    out=0;
    item=0;
    full = new Sem(0);
    empty = new Sem(BUFF_SIZE);
    mutex = new pthread_mutex_t();
    pthread_mutex_init(mutex, NULL);
}

ProducerConsumer::~ProducerConsumer()
{
    delete full;
    delete empty;
    delete mutex;
}

void ProducerConsumer::run()
{
	thread *idP[NP], *idC[NC];
    int index;

    for (index = 0; index < NP; index++)
    {
        /* Create a new producer */
        idP[index] = new thread(&ProducerConsumer::Producer,this,this,index);
    }
    /*create a new Consumer*/
    for(index=0; index<NC; index++)
    {
        idC[index] = new thread(&ProducerConsumer::Consumer, this,this,index);
    }

//    for(int i=0;i<NP;i++)
//        delete idP[i];
//    for(int i=0;i<NC;i++)
//        delete idC[i];

    pthread_exit(NULL);
}

void* ProducerConsumer::Producer(ProducerConsumer *parent,int index)
{
    // int parent->item=0;

//    ProducerConsumer *parent = (ProducerConsumer*)arg;


    while(1)
    {
        /* If there are no empty slots, wait */
        parent->empty->wait();
        /* If another thread uses the buffer, wait */
        pthread_mutex_lock(parent->mutex);
        parent->buf[parent->in] = parent->item;
        parent->in = (parent->in+1)%BUFF_SIZE;
        printf("%d Producer, Producing %d\n", index, parent->item);
        fflush(stdout);
        parent->item++;
        /* Release the buffer */
        pthread_mutex_unlock(parent->mutex);
        /* Increment the number of full slots */
        parent->full->signal();

        sleep(1);
    }
   // return NULL;
}

void* ProducerConsumer::Consumer(ProducerConsumer *parent,int index)
{
    // int parent->item=0;

//    ProducerConsumer *parent = (ProducerConsumer*)arg;

    while(1)
    {
        parent->full->wait();
        pthread_mutex_lock(parent->mutex);
        //parent->item++;
        int item=parent->buf[parent->out];
        parent->out = (parent->out+1)%BUFF_SIZE;
        printf("\t%d Consumer, Consuming  %d\n", index, item);
        fflush(stdout);
        /* Release the buffer */
        pthread_mutex_unlock(parent->mutex);
        /* Increment the number of full slots */
        parent->empty->signal();

        sleep(1);
    }
//    return NULL;
}
