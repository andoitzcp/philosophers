#include "philo.h"

void set_params(t_params *params, int argc, char **argv)
{
    params->nop = ft_atoi(argv[1]);
    params->ttd = ft_atoi(argv[2]);
    params->tte = ft_atoi(argv[3]);
    params->tts = ft_atoi(argv[4]);
    if (argc == 6)
        params->nme = ft_atoi(argv[5]);
    else
        params->nme = -1;
    return ;
}

pthread_mutex_t *init_mutex(t_prompt *prompt)
{
    pthread_mutex_t *fork;

    fork = malloc(sizeof(pthread_mutex_t));
    if (!fork)
        exit_on_error(prompt, "philosophers: init_mutex: fork");
    return (fork);
}

struct timeval *init_timevalue(t_prompt *prompt)
{
    struct timeval *tv;

    tv = malloc(sizeof(struct timeval));
    if (!tv)
        exit_on_error(prompt, "philosophers: init_timevalue: tv");
    tv->tv_sec = 0;
    tv->tv_usec = 0;
    return (tv);
}

t_philo *init_philo(t_prompt *prompt, pthread_mutex_t **tmp_forks)
{
    static int i = 0;
    t_philo *p;
    int nop;

    nop = prompt->params->nop;
    p = malloc(sizeof(t_philo));
    if (!p)
        exit_on_error(prompt, "philosophers: init_philo: p");
    p->nbr = i;
    p->lfm = tmp_forks[i % nop];
    p->rfm = tmp_forks[(i + 1) % nop];
    p->lpn = NULL;
    p->rpn = NULL;
    p->last_m = init_timevalue(prompt);
    p->time_s = init_timevalue(prompt);
    p->count_m = 0;
    p->prompt = prompt;
    i++;
    return (p);
}

void build_table(t_prompt *prompt, t_philo **tmp_table)
{
    t_philo **head;
    t_philo *p;
    int nop;
    int i;

    nop = prompt->params->nop;
    head = malloc(sizeof(t_philo *));
    if (!head)
        exit_on_error(prompt, "philosophers: build_table: head");
    *head = tmp_table[0];
    prompt->table = head;
    i = 0;
    while (i < nop)
    {
        p = tmp_table[i];
        p->lpn = tmp_table[ft_abs((i - 1) % nop)];
        p->rpn = tmp_table[ft_abs((i + 1) % nop)];
        i++;
    }
}

// Creates a table structure, which is a circular double linked list. Each node
// in the structure represents a philosopher which has a fork (pthread_mutes_t)
// to the right and another to the left. also, each philosopher has 2 adyacent
// philosphers represented as a pointer to a t_philo node address.
void init_table(t_prompt *prompt)
{
    t_philo **tmp_table;
    pthread_mutex_t **tmp_forks;
    int nop;
    int i;

    nop = prompt->params->nop;
    tmp_forks = malloc(sizeof(pthread_mutex_t *) * nop);
    if (!tmp_forks)
        exit_on_error(prompt, "philosophers: init_table: tmp_forks");
    i = 0;
    while (i < nop)
        tmp_forks[i++] = init_mutex(prompt);
    tmp_table = malloc(sizeof(t_philo *) * nop);
    if (!tmp_table)
        exit_on_error(prompt, "philosophers: init_table: tmp_table");
    i = 0;
    while (i < nop)
        tmp_table[i++] = init_philo(prompt, tmp_forks);
    i = 0;
    build_table(prompt, tmp_table);
    free(tmp_table);
    free(tmp_forks);
}

t_prompt *init_prompt()
{
    t_prompt *prompt;

    prompt = malloc(sizeof(t_prompt));
    if (prompt == NULL)
        exit_on_error(prompt, "philosophers: init_prompt: prompt");
    prompt->params = malloc(sizeof(t_params));
    if (prompt->params == NULL)
        exit_on_error(prompt, "philosophers: init_prompt: params");
    prompt->table = malloc(sizeof(t_philo *));
    if (prompt->table== NULL)
        exit_on_error(prompt, "philosophers: init_prompt: table");
    prompt->print_mutex = init_mutex(prompt);
    if (prompt->print_mutex== NULL)
        exit_on_error(prompt, "philosophers: init_prompt: print_mutex");
    return (prompt);
}
