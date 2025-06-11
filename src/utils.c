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
    return i;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cdst;
	char	*csrc;
	size_t	index;

	if (!dst && !src)
		return (dst);
	cdst = (char *)dst;
	csrc = (char *)src;
	index = 0;
	while (index < n)
	{
		cdst[index] = csrc[index];
		index++;
	}
	return (dst);
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
