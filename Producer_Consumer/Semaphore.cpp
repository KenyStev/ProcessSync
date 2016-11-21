#include "Semaphore.h"

Sem::Sem(int value)
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
