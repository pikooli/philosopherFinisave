/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:19:16 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 14:53:22 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void		ft_putnbr(long long nbr)
{
	char c;

	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = nbr % 10 + '0';
	write(1, &c, 1);
}

long long	ft_atoi(char *str)
{
	long long nb;

	nb = 0;
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (-1);
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb);
}

int			get_arg(t_data *g_data, int ac, char **av)
{
	if ((g_data->nb_philo = ft_atoi(av[1])) < 0)
		return (1);
	if ((g_data->time_die = ft_atoi(av[2])) < 0)
		return (1);
	if ((g_data->time_eat = ft_atoi(av[3]) * 1000) < 0)
		return (1);
	if ((g_data->time_sleep = ft_atoi(av[4]) * 1000) < 0)
		return (1);
	g_data->nb_eat = -1;
	if (ac == 6)
		if ((g_data->nb_eat = ft_atoi(av[5])) < 0)
			return (1);
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
