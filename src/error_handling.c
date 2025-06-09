#include "philo.h"

void free_philo(t_philo *philo)
{
    (void)philo; // TODO
    return ;
}

void free_table(t_philo **head)
{
    (void)head; // TODO
    return ;
}

void cleanup(t_prompt *prompt)
{
    if (!prompt)
        return ;
    if (prompt->params)
        free(prompt->params);
    if (prompt->table)
        free_table(prompt->table);
    return ;
}

void exit_on_error(t_prompt *prompt, char *s)
{
    cleanup(prompt);
    perror(s);
    exit(EXIT_FAILURE);
}
