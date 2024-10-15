#include "philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

void *routine()
{
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    printf("Routine\n");
    printf("Philosopher #%d eats: %ld\n", 1 , tv.tv_sec);
    return (NULL);
}

int ft_atoi(char *s)
{
    int sign;
    unsigned int n;

    sign = 1;
    if (*s == '-' || *s == '+')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }
    n = 0;
    while (*s != '\0')
    {
        if (*s < '0' || *s > '9')
            return ((int)(n * sign));
        n *= 10;
        n += *s - '0';
        s++;
    }
    return ((int)(n * sign));
}

t_philo *ft_initphilo(void)
{
    static int i = 0;
    t_philo *p;
    pthread_mutex_t *fork;

    p = malloc(sizeof(t_philo));
    fork = malloc(sizeof(pthread_mutex_t));
    if (!p || !fork)
    {
        perror("ft_initphilo:malloc:");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&p->thr, NULL, &routine, NULL) != 0)
    {
        perror("ft_initphilo:thread_create:");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_init(fork, NULL) != 0)
    {
        perror("ft_initphilo:thread_create:");
        exit(EXIT_FAILURE);
    }
    i++;
    i = p->nbr;
    p->lfm = fork;
    return (p);
}

void ft_jointhreads(t_philo **head)
{
    t_philo *p;

    p = *head;
    while (p->rpn != *head)
    {
        if (pthread_join(p->thr, NULL) != 0)
        {
            perror("ft_jointhreads:thread_join:");
            exit(EXIT_FAILURE);
        }
        p = p->rpn;
    }
    if (pthread_join(p->thr, NULL) != 0)
    {
        perror("ft_jointhreads:thread_join:");
        exit(EXIT_FAILURE);
    }
}

void ft_iterandlinkphilo(t_philo *p1, t_philo *p2, char mode)
{
    if (mode == 'f')
    {
        p1->lpn = p2;
        p2 = p1;
        p1 = p1->rpn;
    }
    if (mode == 'r')
    {
        p1->rpn = p2;
        p1->rfm = p2->lfm;
        p2 = p1;
        p1 = p1->lpn;
    }

}

void ft_inittable(t_philo **head, t_params *params)
{
    int i;
    t_philo *p;
    t_philo *tmp;

    i = 0;
    tmp = NULL;
    while (i++ < params->nop)
    {
        p = ft_initphilo();
        if (*head == NULL)
            *head = p;
        p->lpn = tmp;
        tmp = p;
        p = p->rpn;
    }
    p = tmp;
    tmp = *head;
    tmp->lpn = p;
    while (i-- > 0)
    {
        p->rpn = tmp;
        p->rfm = tmp->lfm;
        tmp = p;
        p = p->lpn;
    }
}


int main(int argc, char **argv)
{
    t_params params;
    t_philo **table;

    if (argc != 5 && argc != 6)
        return (EXIT_FAILURE);
    params.nop = ft_atoi(argv[1]);
    params.ttd = ft_atoi(argv[2]);
    params.tte = ft_atoi(argv[3]);
    params.tts = ft_atoi(argv[4]);
    if (argc == 6)
        params.tts = ft_atoi(argv[5]);
    ft_printparams(&params);
    table = (t_philo **)malloc(sizeof(t_philo *));
    if (!table)
        return (EXIT_FAILURE);
    *table = NULL;
    ft_inittable(table, &params);
    ft_printtable(table);
    ft_jointhreads(table);
    return (0);
}
