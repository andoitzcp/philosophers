/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acampo-p@student.42urduliz.com <marvi      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:06:43 by acampo-p@         #+#    #+#             */
/*   Updated: 2025/08/24 16:10:07 by acampo-p@        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_tstamp(t_tstamp *tstamp)
{
	tstamp->tv.tv_sec = 0;
	tstamp->tv.tv_usec = 0;
	tstamp->usecs = 0;
	pthread_mutex_init(&(tstamp->mtx), NULL);
}

void	update_tstamp(t_tstamp *tstamp)
{
	pthread_mutex_lock(&(tstamp->mtx));
	gettimeofday(&(tstamp->tv), NULL);
	tstamp->usecs = tstamp->tv.tv_sec * 1000000 + tstamp->tv.tv_usec;
	pthread_mutex_unlock(&(tstamp->mtx));
}

unsigned long	get_tstamp_usecs(t_tstamp *tstamp)
{
	unsigned long int	usecs;

	pthread_mutex_lock(&(tstamp->mtx));
	usecs = tstamp->usecs;
	pthread_mutex_unlock(&(tstamp->mtx));
	return (usecs);
}

void	run_routine_loop(t_philo *philo)
{
	while (is_philo_finished_eating(philo->prompt, philo) == 0)
	{
		if (get_death_flag(philo->prompt) == 1)
			break ;
		action_take_forks(philo);
		if (get_death_flag(philo->prompt) == 1)
		{
			pthread_mutex_unlock(philo->lfm);
			pthread_mutex_unlock(philo->rfm);
			break ;
		}
		action_eat(philo);
		if (get_death_flag(philo->prompt) == 1)
			break ;
		action_sleep(philo);
		if (get_death_flag(philo->prompt) == 1)
			break ;
		action_think(philo);
		if (get_death_flag(philo->prompt) == 1)
			break ;
	}
	return ;
}

void	*routine(void *p)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)p;
	params = philo->prompt->params;
	action_think(philo);
	usleep(params->ttd * philo->nbr / 100);
	run_routine_loop(philo);
	return (p);
}
