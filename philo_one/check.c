/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:10:41 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/15 12:07:31 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_lasteat(t_philo *philo)
{
	long long time;

	time = ft_get_time();
	if ((time - philo->lasteat) > philo->data.time_die)
	{
		philo->state = DIED;
		ft_annonce(DIED, philo, time);
		return (1);
	}
	return (0);
}

int		ft_check_state(t_philo *philo)
{
	int			i;
	long long	time;

	while (1)
	{
		i = -1;
		while (++i < philo[0].data.nb_philo)
		{
			time = ft_get_time();
			pthread_mutex_lock(&philo[i].mutex);
			if (philo[i].count == philo->data.nb_eat - 1)
			{
				pthread_mutex_lock(&g_mutex);
				return (1);
			}
			if (philo[i].state != EAT &&
					((time - philo[i].lasteat) > philo->data.time_die + 5))
			{
				ft_annonce(DIED, &philo[i], time);
				return (1);
			}
			pthread_mutex_unlock(&philo[i].mutex);
		}
	}
	return (0);
}
