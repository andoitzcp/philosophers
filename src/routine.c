#include "philo.h"

// valgrind --tool=helgrind --tool=drd

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

    prompt = philo->prompt;
    usecs = get_time_in_microseconds(philo->time_s) / 1000;
    pthread_mutex_lock(prompt->print_mutex);
    if (philo->prompt->someone_has_died == 0)
        printf("%ld %d %s\n", usecs, philo->nbr, s);
    pthread_mutex_unlock(prompt->print_mutex);
}

int action_take_forks(t_philo *philo)
{
	if (philo->nbr % 2 == 0)
    	pthread_mutex_lock(philo->lfm);
	else
    	pthread_mutex_lock(philo->rfm);
    gettimeofday(philo->time_s, 0);
    Announce(philo, ANNOUNCE_FORK);
	if (philo->nbr % 2 == 0)
    	pthread_mutex_lock(philo->rfm);
	else
    	pthread_mutex_lock(philo->lfm);
    gettimeofday(philo->time_s, 0);
    Announce(philo, ANNOUNCE_FORK);
    return (1);
}

int action_eat(t_philo *philo)
{
    t_params *params;

    params = philo->prompt->params;
    gettimeofday(philo->time_s, 0);
    Announce(philo, ANNOUNCE_EAT);
    usleep(params->tte);
    pthread_mutex_unlock(philo->lfm);
    pthread_mutex_unlock(philo->rfm);
    ft_memcpy(&(philo->last_m->tv_sec), &(philo->time_s->tv_sec),
              sizeof(time_t));
    ft_memcpy(&(philo->last_m->tv_usec), &(philo->time_s->tv_usec),
              sizeof(suseconds_t));
    return (1);
}

int action_sleep(t_philo *philo)
{
    t_params *params;

    params = philo->prompt->params;
    gettimeofday(philo->time_s, 0);
    Announce(philo, ANNOUNCE_SLEEP);
    usleep(params->tts);
    return (1);
}

int action_think(t_philo *philo)
{
    gettimeofday(philo->time_s, 0);
    Announce(philo, ANNOUNCE_THINK);
    return (1);
}

void *routine(void *p)
{
    int i;
    t_philo *philo;
    t_params *params;

    philo = (t_philo *)p;
    params = philo->prompt->params;
    i = 0;
    while (i++ < params->nme)
    {
        if (philo->prompt->someone_has_died == 1)
            break ;
		usleep(10);
        action_take_forks(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		usleep(10);
        action_eat(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		usleep(10);
        action_sleep(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		usleep(10);
        action_think(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		usleep(10);
    }
    return (p);
}
