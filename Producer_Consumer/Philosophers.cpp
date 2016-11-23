#include "Philosophers.h"

Philosophers::Philosophers(Semaphore *sem)
{
    NF = sem->value;
    turn = new Sem(sem->value/2);
    sticks = sem;
}

Philosophers::~Philosophers()
{
    delete sticks;
}

void Philosophers::run()
{
    thread *idF[NF];

    for(int index=0; index<NF; index++)
    {
        idF[index] = new thread(&Philosophers::Eat, this,this,index);
    }

    pthread_exit(NULL);
}

void* Philosophers::Eat(Philosophers*parent,int index)
{
    while(1)
    {
        parent->turn->wait();

        parent->sticks->wait();
        printf("F_%d waiting to eat\n",index);

        parent->sticks->wait();

        sleep(1);
        printf("F_%d ate a bit\n",index);

        parent->sticks->signal();

        parent->turn->signal();
//        printf("F_%d left a stick\n",index);

        parent->sticks->signal();
//        printf("F_%d left both sticks\n",index);
        usleep(1);
    }
}
