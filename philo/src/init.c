/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acampo-p@student.42urduliz.com <marvi      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:05:10 by acampo-p@         #+#    #+#             */
/*   Updated: 2025/08/24 15:41:07 by acampo-p@        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_params(t_params *params, int argc, char **argv)
{
	params->nop = ft_atoi(argv[1]);
	params->ttd = ft_atoi(argv[2]) * 1000;
	params->tte = ft_atoi(argv[3]) * 1000;
	params->tts = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		params->nme = ft_atoi(argv[5]);
	else
		params->nme = -1;
	return ;
}

void	init_philo(t_prompt *prompt, t_philo *philo, pthread_mutex_t *forks)
{
	static int	i = 0;
	int			nop;

	nop = prompt->params->nop;
	philo->nbr = i + 1;
	philo->lfm = &forks[i % nop];
	philo->rfm = &forks[(i + 1) % nop];
	pthread_mutex_init(&(philo->mcm), NULL);
	philo->lpn = NULL;
	philo->rpn = NULL;
	init_tstamp(&(philo->tsf));
	init_tstamp(&(philo->tsm));
	init_tstamp(&(philo->tss));
	init_tstamp(&(philo->tst));
	init_tstamp(&(philo->tsd));
	philo->count_m = 0;
	philo->prompt = prompt;
	i++;
}

void	build_table(t_prompt *prompt, t_philo *philos)
{
	t_philo	**head;
	t_philo	*p;
	int		nop;
	int		i;

	nop = prompt->params->nop;
	head = prompt->table;
	*head = &philos[0];
	prompt->table = head;
	i = 0;
	while (i < nop)
	{
		p = &philos[i];
		p->lpn = &philos[ft_abs((i - 1) % nop)];
		p->rpn = &philos[ft_abs((i + 1) % nop)];
		i++;
	}
}

void	init_table(t_prompt *prompt, t_philo *philos, pthread_mutex_t *forks)
{
	int	nop;
	int	i;

	nop = prompt->params->nop;
	i = 0;
	while (i < nop)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < nop)
		init_philo(prompt, &philos[i++], forks);
	i = 0;
	build_table(prompt, philos);
}

void	init_prompt(t_prompt *prompt, t_params *params, t_philo **table)
{
	prompt->params = params;
	prompt->table = table;
	pthread_mutex_init(&(prompt->print_mutex), NULL);
	pthread_mutex_init(&(prompt->death_mutex), NULL);
	return ;
}
