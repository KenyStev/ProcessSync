void perror_exit(char *s);

pthread_mutex_t *make_mutex();
void mutex_lock(pthread_mutex_t *mutex);
void mutex_unlock(pthread_mutex_t *mutex);

pthread_cond_t *make_cond();
void cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
void cond_signal(pthread_cond_t *cond);
