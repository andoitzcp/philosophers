#include "philo.h"

int is_alive_philo(t_philo *philo)
{
    unsigned long death_time;
    unsigned long current_time;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (get_tstamp_usecs(&(philo->tsm)) == 0)
        return (1);
    death_time = get_tstamp_usecs(&(philo->tsm)) + philo->prompt->params->ttd;
    current_time = tv.tv_sec * 1000000 + tv.tv_usec;
    if (death_time < current_time)
        return (0);
    else
        return (1);
}

int is_philo_finished_eating(t_prompt *prompt, t_philo *philo)
{
    int target;

    target = prompt->params->nme;
    if (target == -1)
        return (0);
    if (philo->count_m < target)
        return (0);
    else
        return (1);
}

int all_have_eaten(t_prompt *prompt)
{
    t_philo *p;

    p = *(prompt->table);
    while (p->rpn != *(prompt->table))
    {
        if (is_philo_finished_eating(prompt, p) == 0)
            return (0);
        p = p->rpn;
    }
    if (is_philo_finished_eating(prompt, p) == 0)
        return (0);
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
        if (all_have_eaten(prompt))
            break ;
        //printf("flag100: %d, %d\n", is_alive_philo(philo), is_philo_finished_eating(prompt, philo));
        if (is_alive_philo(philo) == 0 && !is_philo_finished_eating(prompt, philo))
        {
            update_tstamp(&(philo->tsd));
            Announce(philo, ANNOUNCE_DEATH, &(philo->tsd));
            prompt->someone_has_died = 1;
            break ;
        }
        if (philo == *head)
            usleep(50);
        philo = philo->rpn;
    }
    /* while (philo->rpn != *head) */
    /* { */
    /*     pthread_detach(philo->thr); */
    /*     philo = philo->rpn; */
    /* } */
    return(p);
}
