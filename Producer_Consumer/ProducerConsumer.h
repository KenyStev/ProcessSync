#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#define BUFF_SIZE   5           /* total number of slots */
#define NP          3           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */

#include <thread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Semaphore.h"

// for sleep
#include <unistd.h>

using namespace std;

class ProducerConsumer
{
    public:
    	int buf[BUFF_SIZE];   /* shared var */
	    int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
	    int out;              /* buf[out%BUFF_SIZE] is the first full slot */
	    int item;
	    Semaphore *full;           /* keep track of the number of full spots */
	    Semaphore *empty;          /* keep track of the number of empty spots */

	    // use correct type here
	    pthread_mutex_t *mutex;

        ProducerConsumer();
        virtual ~ProducerConsumer();
        void *Producer(ProducerConsumer *parent,int);
        void *Consumer(ProducerConsumer *parent,int);
        void run();
    protected:
    private:
};

#endif // PRODUCERCONSUMER_H
