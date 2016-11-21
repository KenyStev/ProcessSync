#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"

void perror_exit(char *s)
{
  perror(s);
  exit(-1);
}
