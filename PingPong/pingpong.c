#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define Buffer_Limit 10
int Buffer_Index_Value = 0;
char *Buffer_Queue;
pthread_mutex_t mutex_variable = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Empty = PTHREAD_COND_INITIALIZER;

void *ping()
{
       while(1)
       {
           pthread_mutex_lock(&mutex_variable);
           if(Buffer_Index_Value == -1)
           {            
               pthread_cond_wait(&Buffer_Queue_Not_Empty, &mutex_variable);
           }
           sleep(1);
           Buffer_Index_Value--;
           printf("ping\n");
           pthread_mutex_unlock(&mutex_variable);        
           pthread_cond_signal(&Buffer_Queue_Not_Full);
           sleep(1);
       }    
}

void *pong()
{
	usleep(1);
    while(1)
        {   
            pthread_mutex_lock(&mutex_variable);
            if(Buffer_Index_Value == Buffer_Limit)
            {                        
                pthread_cond_wait(&Buffer_Queue_Not_Full, &mutex_variable);
            }                        
            Buffer_Index_Value++;
            sleep(1);
            printf("pong\n");
            pthread_mutex_unlock(&mutex_variable);
            pthread_cond_signal(&Buffer_Queue_Not_Empty);
            sleep(1);
        }
}

int main()
{    
    pthread_t pong_thread_id, ping_thread_id;
    Buffer_Queue = (char *) malloc(sizeof(char) * Buffer_Limit);            
    pthread_create(&ping_thread_id, NULL, ping, NULL);
    pthread_create(&pong_thread_id, NULL, pong, NULL);
    pthread_join(pong_thread_id, NULL);
    pthread_join(ping_thread_id, NULL);
    return 0;
}