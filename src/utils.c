/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acampo-p@student.42urduliz.com <marvi      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:08:20 by acampo-p@         #+#    #+#             */
/*   Updated: 2025/08/24 14:13:22 by acampo-p@        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str && str[index] != '\0')
		index += 1;
	return (index);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write (fd, s, ft_strlen(s));
}

int	ft_abs(int i)
{
	if (i < 0)
		return (-1 * i);
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	nbr;

	sign = 1;
	nbr = 0;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr) == 1)
	{
		nbr += *nptr - '0';
		nbr *= 10;
		nptr++;
	}
	nbr = nbr * sign / 10;
	return ((int)nbr);
}
