#include "philo.h"

void *routine(void *p)
{
    (void)p;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    printf("Routine\n");
    printf("Philosopher #%d eats: %ld\n", 1 , tv.tv_sec);
    return (NULL);
}
