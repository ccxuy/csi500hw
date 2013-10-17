#include "racer.h"
#include <pthread.h>

#ifdef CONFIG_VOLATILE 
volatile
#endif
int ring = 0;

void  * racer(void *tid)
{
  int count;
  pthread_mutex_lock(&mutex);
  for(count = nLoops; count > 0; count--)
    {
      ring = ring + 1;
    }
  pthread_mutex_unlock(&mutex);
}
