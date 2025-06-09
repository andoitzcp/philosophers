#include "philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

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

void jointhreads(t_prompt *prompt)
{
    t_philo **head;
    t_philo *p;

    head = prompt->table;
    p = *head;
    while (p->rpn != *head)
    {
        if (pthread_join(p->thr, NULL) != 0)
            exit_on_error(prompt, "philosophers:jointhreads:thread");
        p = p->rpn;
    }
}

void create_threads(t_prompt *prompt)
{
    t_philo *p;

    p = *(prompt->table);
    while(p->rpn != *(prompt->table))
    {
        if (pthread_create(&p->thr, NULL, routine, NULL) != 0)
            exit_on_error(prompt, "philosophers:initphilo:thread");
        p = p->rpn;
    }
}

int main(int argc, char **argv)
{
    t_prompt *prompt;

    if (argc != 5 && argc != 6)
    {
        ft_putstr_fd("philosophers:main:incorrect number of arguments\n", 2);
        return (EXIT_FAILURE);
    }
    prompt = init_prompt();
    set_params(prompt->params, argc, argv);
    ft_printparams(prompt->params);
    prompt->table = NULL;
    init_table(prompt);
    ft_printtable(prompt->table);
    create_threads(prompt);
    jointhreads(prompt);
    return (EXIT_SUCCESS);
}
