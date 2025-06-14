#include "philo.h"

int is_alive_philo(t_philo *philo)
{
    unsigned long time_to_die;
    unsigned long death_time;
    unsigned long current_time;
    struct timeval tv;
    struct timeval tv2;

    gettimeofday(&tv, NULL);
    time_to_die = philo->prompt->params->ttd;
    tv2.tv_sec = philo->last_m.tv_sec;
    tv2.tv_usec = time_to_die + philo->last_m.tv_usec;
    if (get_time_in_microseconds(philo->last_m) == 0)
        return (1);
    death_time = get_time_in_microseconds(tv2);
    current_time = get_time_in_microseconds(tv);
    fprintf(stdout, "flag100: nbr=%d, dt=%ld, ct=%ld, dt-ct=%ld\n", philo->nbr, death_time, current_time, death_time - current_time);
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
        if (is_alive_philo(philo) == 0 && !is_philo_finished_eating(prompt, philo))
        {
            Announce(philo, ANNOUNCE_DEATH);
            prompt->someone_has_died = 1;
            break ;
        }
        //if (philo == *head)
            //usleep(50);
        philo = philo->rpn;
    }
    /* while (philo->rpn != *head) */
    /* { */
    /*     pthread_detach(philo->thr); */
    /*     philo = philo->rpn; */
    /* } */
    return(p);
}
