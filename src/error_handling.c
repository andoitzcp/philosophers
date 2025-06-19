#include "philo.h"

int is_number(char *s)
{
    int i;

    i = 0;
    if (!s && s[i] == '\0')
        return (0);
    if (s[i] == '-' || s[i] == '+')
        i++;
    while (s[i] != '\0')
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

int is_valid_input_args(char **argv)
{
    int i;

    i = 0;
    while (argv[i] != NULL)
    {
        if (!is_number(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

void exit_on_error(char *s, int exit_mode)
{
    if (exit_mode == EXIT_MODE_PUTSTR)
        ft_putstr_fd(s, 2);
    else
        perror(s);
    exit(EXIT_FAILURE);
}

void check_input_params(t_params *params)
{
    if (params->nop > MAX_PHILO_NUMBER)
        exit_on_error(ERROR_STR_03, EXIT_MODE_PUTSTR);
    if (params->nop < 0)
        exit_on_error(ERROR_STR_04, EXIT_MODE_PUTSTR);
    if (params->tte < 0 || params->nop < 0|| params->tts < 0|| params->ttd < 0)
        exit_on_error(ERROR_STR_05, EXIT_MODE_PUTSTR);
    if (params->nme != -1 && params->nme < 1)
        exit_on_error(ERROR_STR_05, EXIT_MODE_PUTSTR);
}
