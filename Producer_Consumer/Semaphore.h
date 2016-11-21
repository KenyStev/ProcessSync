#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "utils.h"

class Semaphore
{
    public:
        Semaphore(){};
        virtual ~Semaphore(){};
        virtual void wait() = 0;
        virtual void signal() = 0;
    protected:
    private:
};

class Sem : public Semaphore
{
public:
	sem_t *semaphore;
	Sem(int value);
	virtual ~Sem();
	void wait();
    void signal();
};

class MySem : public Semaphore
{
public:
	int value, wakeups;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;

	MySem(int value);
	virtual ~MySem();
	void wait();
    void signal();
};

#endif // SEMAPHORE_H
