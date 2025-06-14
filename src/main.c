#include "philo.h"

void jointhreads(t_prompt *prompt)
{
    t_philo **head;
    t_philo *p;

    if (pthread_join(prompt->orchttr, NULL) != 0)
        exit_on_error(prompt, "philosophers: jointhreads: orchttr");
    head = prompt->table;
    p = *head;
    while (p->rpn != *head)
    {
        if (pthread_join(p->thr, NULL) != 0)
            exit_on_error(prompt, "philosophers: jointhreads: thread");
        p = p->rpn;
    }
    if (pthread_join(p->thr, NULL) != 0)
        exit_on_error(prompt, "philosophers: jointhreads: thread");
}

void create_threads(t_prompt *prompt)
{
    t_philo *p;

    if (pthread_create(&prompt->orchttr, NULL, control, prompt) != 0)
        exit_on_error(prompt, "philosophers: initphilo: orchttr");
    p = *(prompt->table);
    while(p->rpn != *(prompt->table))
    {
        if (pthread_create(&p->thr, NULL, routine, p) != 0)
            exit_on_error(prompt, "philosophers: initphilo: thread");
        p = p->rpn;
    }
    if (pthread_create(&p->thr, NULL, routine, p) != 0)
        exit_on_error(prompt, "philosophers: initphilo: thread");
}

int main(int argc, char **argv)
{
    t_prompt prompt;
    t_params params;
    t_philo *table;
    t_philo philos[200];
    pthread_mutex_t forks[200];

    if (argc != 5 && argc != 6)
    {
        ft_putstr_fd("philosophers: main: incorrect number of arguments\n", 2);
        return (EXIT_FAILURE);
    }
    init_prompt(&prompt, &params, &table);
    set_params(&params, argc, argv);
    ft_printparams(&params);
    prompt.table[0] = NULL;
    init_table(&prompt, philos, forks);
	ft_printtable(&table);
    prompt.someone_has_died = 0;
    create_threads(&prompt);
    jointhreads(&prompt);
    return (EXIT_SUCCESS);
}
