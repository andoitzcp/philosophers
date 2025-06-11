#include "philo.h"

unsigned long get_time_in_microseconds(struct timeval *tv)
{
    time_t seconds;
    suseconds_t microseconds;
    unsigned long usecs;

    seconds = tv->tv_sec;
    microseconds = tv->tv_usec;
    usecs = 1000000 * seconds + microseconds;
    return (usecs);
}

void Announce(t_philo *philo, char *s)
{
    t_prompt *prompt;
    unsigned long usecs;

    prompt = philo->prompt; // pendiente linkar a cada filosofo el prompt TODO
    usecs = get_time_in_microseconds(philo->time_s);
    pthread_mutex_lock(prompt->print_mutex); //pendiente de inicializarlo TODO
    printf("%ld %d %s", usecs, philo->nbr, s);
    pthread_mutex_unlock(prompt->print_mutex); //pendiente de inicializarlo TODO
}

int action_take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->lfm);
    gettimeofday(philo->time_s, NULL);
    Announce(philo, ANNOUNCE_FORK);
    pthread_mutex_lock(philo->lfm);
    Announce(philo, ANNOUNCE_FORK);
    return (1);
}

int action_eat(t_philo *philo)
{
    Announce(philo, ANNOUNCE_EAT);
    return (0); // borrar
}

int action_sleep(t_philo *philo)
{
    Announce(philo, ANNOUNCE_SLEEP);
    return (0); // borrar
}

int action_think(t_philo *philo)
{
    Announce(philo, ANNOUNCE_THINK);
    return (0); // borrar
}

void *routine(void *p)
{
    int i;
    t_philo *philo;
    t_params *params;

    philo = (t_philo *)p;
    params = philo->prompt->params;
    while (i++ < params->nme)
    {
        action_take_forks(philo);
        action_eat(philo);
        action_sleep(philo);
        action_think(philo);
    }
    return (p);
}
