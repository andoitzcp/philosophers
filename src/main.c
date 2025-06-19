#include "philo.h"


void jointhreads(t_prompt *prompt)
{
    t_philo **head;
    t_philo *p;

    if (pthread_join(prompt->orchttr, NULL) != 0)
        exit_on_error("philosophers: jointhreads: orchttr", EXIT_MODE_PERROR);
    head = prompt->table;
    p = *head;
    while (p->rpn != *head)
    {
        if (pthread_join(p->thr, NULL) != 0)
            exit_on_error("philosophers: jointhreads: thread", EXIT_MODE_PERROR);
        p = p->rpn;
    }
    if (pthread_join(p->thr, NULL) != 0)
        exit_on_error("philosophers: jointhreads: thread", EXIT_MODE_PERROR);
}

void create_threads(t_prompt *prompt)
{
    t_philo *p;

    if (pthread_create(&prompt->orchttr, NULL, control, prompt) != 0)
        exit_on_error("philosophers: initphilo: orchttr", EXIT_MODE_PERROR);
    p = *(prompt->table);
    while(p->rpn != *(prompt->table))
    {
        if (pthread_create(&p->thr, NULL, routine, p) != 0)
            exit_on_error("philosophers: initphilo: thread", EXIT_MODE_PERROR);
        p = p->rpn;
    }
    if (pthread_create(&p->thr, NULL, routine, p) != 0)
        exit_on_error("philosophers: initphilo: thread", EXIT_MODE_PERROR);
}

int main(int argc, char **argv)
{
    t_prompt prompt;
    t_params params;
    t_philo *table;
    t_philo philos[MAX_PHILO_NUMBER];
    pthread_mutex_t forks[MAX_PHILO_NUMBER];

    if (argc != 5 && argc != 6)
        exit_on_error(ERROR_STR_01, EXIT_MODE_PUTSTR);
    if (!is_valid_input_args(argv))
        exit_on_error(ERROR_STR_02, EXIT_MODE_PUTSTR);
    init_prompt(&prompt, &params, &table);
    set_params(&params, argc, argv);
    check_input_params(&params);
    //ft_printparams(&params);
    prompt.table[0] = NULL;
    init_table(&prompt, philos, forks);
	//ft_printtable(&table);
    prompt.someone_has_died = 0;
    create_threads(&prompt);
    jointhreads(&prompt);
    return (EXIT_SUCCESS);
}
