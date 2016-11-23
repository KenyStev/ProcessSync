#include "Semaphore.h"

Sem::Sem(int value) : Semaphore(value)
{
	semaphore = new sem_t();
	int n = sem_init(semaphore, 0, value);
	if (n != 0) perror_exit("sem_init failed");
}

Sem::~Sem()
{
    delete semaphore;
}

void Sem::wait()
{
	int n = sem_wait(semaphore);
	if (n != 0) perror_exit("sem_wait failed");
}

void Sem::signal()
{
	int n = sem_post(semaphore);
	if (n != 0) perror_exit("sem_post failed");
}

/** MySem Implementation */
MySem::MySem(int value) : Semaphore(value)
{
	wakeups = 0;
	mutex = make_mutex();
	cond = make_cond();
}

MySem::~MySem()
{
    delete mutex;
    delete cond;
}

void MySem::wait()
{
	mutex_lock(mutex);
    value--;

    if (value < 0) {
        do {
            cond_wait(cond,mutex);
        } while (wakeups < 1);
        wakeups--;
    }
    mutex_unlock(mutex);
}

void MySem::signal()
{
    mutex_lock(mutex);
    value++;

    if (value <= 0) {
        wakeups++;
        cond_signal(cond);
    }
    mutex_unlock(mutex);
}
