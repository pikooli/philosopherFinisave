/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:10:41 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 15:00:53 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check_state(t_philo *philo)
{
	long long	time;

	while (1)
	{
		sem_wait(philo->sem);
		time = ft_get_time();
		if (philo->count == philo->data.nb_eat - 1)
		{
			sem_wait(g_sem);
			sem_post(g_dead);
		}
		if (philo->state != EAT &&
				((time - philo->lasteat) > philo->data.time_die + 5))
		{
			ft_annonce(DIED, philo, time);
			sem_post(g_dead);
			return (0);
		}
		sem_post(philo->sem);
	}
	return (0);
}
