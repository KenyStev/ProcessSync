#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"

void perror_exit(char *s)
{
  perror(s);
  exit(-1);
}

pthread_mutex_t *make_mutex()
{
  pthread_mutex_t *mutex = new pthread_mutex_t();
  int n = pthread_mutex_init(mutex, NULL);
  if (n != 0) perror_exit("make_lock failed");
  return mutex;
}

void mutex_lock(pthread_mutex_t *mutex)
{
  int n = pthread_mutex_lock(mutex);
  if (n != 0) perror_exit("lock failed");
}

void mutex_unlock(pthread_mutex_t *mutex)
{
  int n = pthread_mutex_unlock(mutex);
  if (n != 0) perror_exit("unlock failed");
}

// COND WRAPPER

pthread_cond_t *make_cond()
{
  pthread_cond_t *cond = new pthread_cond_t();
  int n = pthread_cond_init(cond, NULL);
  if (n != 0) perror_exit("make_cond failed");

  return cond;
}

void cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
  int n = pthread_cond_wait(cond, mutex);
  if (n != 0) perror_exit("cond_wait failed");
}

void cond_signal(pthread_cond_t *cond)
{
  int n = pthread_cond_signal(cond);
  if (n != 0) perror_exit("cond_signal failed");
}
