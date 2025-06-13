#include "philo.h"

int is_alive_philo(t_philo *philo)
{
    unsigned long time_to_die;
    unsigned long death_time;
    unsigned long current_time;
    struct timeval tv;
    struct timeval tv2;

    time_to_die = philo->prompt->params->ttd;
    tv2.tv_sec = philo->last_m->tv_sec;
    tv2.tv_usec = time_to_die + philo->last_m->tv_usec;
    if (get_time_in_microseconds(philo->last_m) == 0)
        return (1);
    gettimeofday(&tv, NULL);
    death_time = get_time_in_microseconds(&tv2);
    current_time = get_time_in_microseconds(&tv);
	//printf("flag00:time to die = %ld\n", death_time - current_time);
    if (death_time < current_time)
        return (0);
    else
        return (1);
}

void *control(void *p)
{
    t_prompt *prompt;
    t_philo **head;
    t_philo *philo;

    prompt = (t_prompt *)p;
    head = prompt->table;
    philo = *head;
    while (philo->rpn)
    {
        if (is_alive_philo(philo) == 0)
        {
            Announce(philo, ANNOUNCE_DEATH);
            prompt->someone_has_died = 1;
            break ;
        }
        if (philo == *head)
            usleep(1000);
        philo = philo->rpn;
    }
    /* while (philo->rpn != *head) */
    /* { */
    /*     pthread_detach(philo->thr); */
    /*     philo = philo->rpn; */
    /* } */
    return(p);
}
