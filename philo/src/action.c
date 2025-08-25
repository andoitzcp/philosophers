/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acampo-p@student.42urduliz.com <marvi      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:57:00 by acampo-p@         #+#    #+#             */
/*   Updated: 2025/08/24 14:57:35 by acampo-p@        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	announce(t_philo *philo, char *s, t_tstamp *ts)
{
	t_prompt		*prompt;
	unsigned long	usecs;

	prompt = philo->prompt;
	usecs = get_tstamp_usecs(ts) / 1000;
	pthread_mutex_lock(&(prompt->print_mutex));
	if (get_death_flag(philo->prompt) == 0)
		printf("%ld %d %s\n", usecs, philo->nbr, s);
	pthread_mutex_unlock(&(prompt->print_mutex));
}

int	action_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->nbr % 2 == 0)
	{
		first_fork = philo->lfm;
		second_fork = philo->rfm;
	}
	else
	{
		first_fork = philo->rfm;
		second_fork = philo->lfm;
	}
	pthread_mutex_lock(first_fork);
	update_tstamp(&(philo->tsf));
	announce(philo, ANNOUNCE_FORK, &(philo->tsf));
	pthread_mutex_lock(second_fork);
	update_tstamp(&(philo->tsf));
	announce(philo, ANNOUNCE_FORK, &(philo->tsf));
	return (1);
}

int	action_eat(t_philo *philo)
{
	t_params	*params;

	pthread_mutex_lock(&(philo->mcm));
	philo->count_m += 1;
	pthread_mutex_unlock(&(philo->mcm));
	params = philo->prompt->params;
	update_tstamp(&(philo->tsm));
	announce(philo, ANNOUNCE_EAT, &(philo->tsm));
	usleep(params->tte);
	pthread_mutex_unlock(philo->lfm);
	pthread_mutex_unlock(philo->rfm);
	return (1);
}

int	action_sleep(t_philo *philo)
{
	t_params	*params;

	params = philo->prompt->params;
	update_tstamp(&(philo->tss));
	announce(philo, ANNOUNCE_SLEEP, &(philo->tss));
	usleep(params->tts);
	return (1);
}

int	action_think(t_philo *philo)
{
	update_tstamp(&(philo->tst));
	announce(philo, ANNOUNCE_THINK, &(philo->tst));
	if (philo->prompt->params->nop == 1)
	{
		update_tstamp(&(philo->tsm));
		usleep(philo->prompt->params->ttd * 2);
	}
	return (1);
}
