#include "philo.h"

void ft_printphilosopher(t_philo *p)
{
    static int i = 0;

    printf("Philo #%d: %p\n", i, p);
    printf("\tright philo: %p\n", p->rpn);
    printf("\tleft  philo: %p\n", p->lpn);
    printf("\tright fork: %p\n", p->rfm);
    printf("\tleft  fork: %p\n\n", p->lfm);
    i++;
}

void ft_printtable(t_philo **head)
{
    t_philo *p;

    p = *head;
    while (p->rpn != *head)
    {
        ft_printphilosopher(p);
        p = p->rpn;
    }
    ft_printphilosopher(p);
}

void ft_printparams(t_params *params)
{
    printf("Number of philosophers: %d\n", params->nop);
    printf("Time to die: %d\n", params->ttd);
    printf("Time to eat: %d\n", params->tte);
    printf("Time to sleep: %d\n", params->tts);
    printf("Number must eat: %d\n", params->nme);
}
