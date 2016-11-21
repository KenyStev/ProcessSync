#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "utils.h"
#include "sem.h"

Semaphore *make_semaphore(int value)
{
  Semaphore *sem = malloc(sizeof(Semaphore));
  int n = sem_init(sem, 0, value);
  if (n != 0) perror_exit("sem_init failed");
  return sem;
}

void semaphore_wait(Semaphore *sem)
{
  int n = sem_wait(sem);
  if (n != 0) perror_exit("sem_wait failed");
}

void semaphore_signal(Semaphore *sem)
{
  int n = sem_post(sem);
  if (n != 0) perror_exit("sem_post failed");
}