/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acampo-p@student.42urduliz.com <marvi      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:00:16 by acampo-p@         #+#    #+#             */
/*   Updated: 2025/08/24 14:24:10 by acampo-p@        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*control(void *p)
{
	t_prompt	*prompt;
	t_philo		**head;
	t_philo		*philo;

	prompt = (t_prompt *)p;
	head = prompt->table;
	philo = *head;
	while (philo->rpn)
	{
		if (all_have_eaten(prompt))
			break ;
		if (!is_alive_philo(philo) && !is_philo_finished_eating(prompt, philo))
		{
			update_tstamp(&(philo->tsd));
			announce(philo, ANNOUNCE_DEATH, &(philo->tsd));
			set_death_flag(prompt, 1);
			break ;
		}
		if (philo == *head)
			usleep(50);
		philo = philo->rpn;
	}
	return (p);
}
