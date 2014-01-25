#include "config.h"
#include <pthread.h>
#define nLoops 20000000

#ifdef CONFIG_VOLATILE 
volatile
#endif 
int ring;
/* ring has static lifetime.
   ring is initialized in racer.c
   All the new threads run racer so
   they all share ring.
*/
pthread_mutex_t mutex;
void * racer( void * arg );

