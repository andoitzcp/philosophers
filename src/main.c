#include "philo.h"
#include <pthread.h>

void *routine()
{
    printf("Routine\n");
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


void ft_initthreads(pthread_t *ths, int n)
{
    int i;

    ths = malloc(n * sizeof(pthread_t *));
    if (!ths)
    {
        perror("ft_initthreads:malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < n)
    {
        if(pthread_create(ths + i, NULL, &routine, NULL) != 0)
        {
            perror("ft_inithread:");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

t_philo *ft_initphilo(void)
{
    t_philo *p;

    p = malloc(sizeof(t_philo));
    if (!p)
    {
        perror("ft_initphilo:malloc:");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&p->t, NULL, &routine, NULL) != 0)
    {
        perror("ft_initphilo:thread:");
        exit(EXIT_FAILURE);
    }
    return (p);
}

void ft_inittable(t_philo **head, t_params *params)
{
    int i;
    t_philo *p;
    t_philo *tmp;
    char *f;


    f = (char *)malloc(params->nop * sizeof(char));
    i = 0;
    while (i < params->nop)
    {
        p = ft_initphilo();
        if (*head == NULL)
            *head = p;
        tmp = p;
        p = p->rp;
    }
}


int main(int argc, char **argv)
{
    pthread_t *ths

    if (argc != 5 || argc != 6)
        return 1;
    return (0);
}
