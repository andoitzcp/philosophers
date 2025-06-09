#include "philo.h"

void set_params(t_params *params, int argc, char **argv)
{
    params->nop = ft_atoi(argv[1]);
    params->ttd = ft_atoi(argv[2]);
    params->tte = ft_atoi(argv[3]);
    params->tts = ft_atoi(argv[4]);
    if (argc == 6)
        params->tts = ft_atoi(argv[5]);
    else
        params->tts = -1;
    return ;
}

t_philo *initphilo(t_prompt *prompt)
{
    static int i = 0;
    t_philo *p;
    pthread_mutex_t *fork;

    p = malloc(sizeof(t_philo));
    if (!p)
        exit_on_error(prompt, "philosophers:initphilo:p");
    fork = malloc(sizeof(pthread_mutex_t));
    if (!fork)
        exit_on_error(prompt, "philosophers:initphilo:fork");
    if (pthread_create(&p->thr, NULL, &routine, NULL) != 0)
        exit_on_error(prompt, "philosophers:initphilo:thread");
    if (pthread_mutex_init(fork, NULL) != 0)
        exit_on_error(prompt, "philosophers:initphilo:mutex");
    i++;
    i = p->nbr;
    p->lfm = fork;
    return (p);
}

// Creates a table structure, which is a circular double linked list. Each node
// in the structure represents a philosopher which has a fork (pthread_mutes_t)
// to the right and another to the left. also, each philosopher has 2 adyacent
// philosphers represented as a pointer to a t_philo node address.
void inittable(t_prompt *prompt, t_philo **head, t_params *params)
{
    int i;
    t_philo *p;
    t_philo *tmp;

    i = 0;
    tmp = NULL;
    while (i++ < params->nop)
    {
        p = initphilo(prompt);
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

t_prompt *init_prompt()
{
    t_prompt *prompt;
    t_params *params;
    t_philo **table;

    prompt = malloc(sizeof(t_params));
    if (prompt == NULL)
        exit_on_error(prompt, "philosophers:init_prompt:prompt:");
    prompt->params = malloc(sizeof(t_params));
    if (prompt->params == NULL)
        exit_on_error(prompt, "philosophers:init_prompt:params:");
    prompt->table = malloc(sizeof(t_philo *));
    if (prompt->params == NULL)
        exit_on_error(prompt, "philosophers:init_prompt:table:");
    return (prompt);
}
