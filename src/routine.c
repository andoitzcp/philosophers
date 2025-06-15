#include "philo.h"
#include <sys/select.h>

// valgrind --tool=helgrind --tool=drd

void init_tstamp(t_tstamp *tstamp)
{
    tstamp->tv.tv_sec = 0;
    tstamp->tv.tv_usec = 0;
    tstamp->usecs = 0;
    pthread_mutex_init(&(tstamp->mtx), NULL);
}

void update_tstamp(t_tstamp *tstamp)
{
    pthread_mutex_lock(&(tstamp->mtx));
    gettimeofday(&(tstamp->tv), NULL);
    tstamp->usecs = tstamp->tv.tv_sec * 1000000 + tstamp->tv.tv_usec;
    pthread_mutex_unlock(&(tstamp->mtx));
}

unsigned long get_tstamp_usecs(t_tstamp *tstamp)
{
    unsigned long int usecs;

    pthread_mutex_lock(&(tstamp->mtx));
    usecs = tstamp->usecs;
    pthread_mutex_unlock(&(tstamp->mtx));
    return (usecs);
}

void Announce(t_philo *philo, char *s, t_tstamp *ts)
{
    t_prompt *prompt;
    unsigned long usecs;

    prompt = philo->prompt;
    usecs = get_tstamp_usecs(ts) / 1000;
    pthread_mutex_lock(&(prompt->print_mutex));
    if (philo->prompt->someone_has_died == 0)
        printf("%ld %d %s\n",usecs, philo->nbr, s);
    pthread_mutex_unlock(&(prompt->print_mutex));
}

int action_take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->lfm);
    update_tstamp(&(philo->tsf));
    Announce(philo, ANNOUNCE_FORK, &(philo->tsf));
    pthread_mutex_lock(philo->rfm);
    update_tstamp(&(philo->tsf));
    Announce(philo, ANNOUNCE_FORK, &(philo->tsf));
    return (1);
}

int action_eat(t_philo *philo)
{
    t_params *params;

    philo->count_m += 1;
    params = philo->prompt->params;
    update_tstamp(&(philo->tsm));
    Announce(philo, ANNOUNCE_EAT, &(philo->tsm));
    usleep(params->tte);
    pthread_mutex_unlock(philo->lfm);
    pthread_mutex_unlock(philo->rfm);
    return (1);
}

int action_sleep(t_philo *philo)
{
    t_params *params;

    params = philo->prompt->params;
    update_tstamp(&(philo->tss));
    Announce(philo, ANNOUNCE_SLEEP, &(philo->tss));
    usleep(params->tts);
    return (1);
}

int action_think(t_philo *philo)
{
    update_tstamp(&(philo->tst));
    Announce(philo, ANNOUNCE_THINK, &(philo->tst));
    return (1);
}

void *routine(void *p)
{
    t_philo *philo;
    t_params *params;

    philo = (t_philo *)p;
    params = philo->prompt->params;
    action_think(philo);
    usleep(params->ttd * philo->nbr / 100);
    while (is_philo_finished_eating(philo->prompt, philo) == 0)
    {
        if (philo->prompt->someone_has_died == 1)
            break ;
		//usleep(10);
        action_take_forks(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		//usleep(10);
        action_eat(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		//usleep(10);
        action_sleep(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
        action_think(philo);
        if (philo->prompt->someone_has_died == 1)
            break ;
		//usleep(10);
		//usleep(10);
    }
    return (p);
}
