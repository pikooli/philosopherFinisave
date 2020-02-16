/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:24:16 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/15 12:00:37 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_check_fork(t_philo *philo)
{
	while (philo->fork[philo->philo].old == philo->philo ||
			philo->fork[philo->prev].old == philo->philo)
	{
	}
	pthread_mutex_lock(&philo->fork[philo->prev].mutex);
	pthread_mutex_lock(&philo->fork[philo->philo].mutex);
	return (0);
}

void	ft_state(t_philo *philo, int state)
{
	if (state == EAT)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->state = EAT;
		philo->lasteat = ft_get_time();
		pthread_mutex_unlock(&philo->mutex);
	}
	if (state == SLEEP)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->state = SLEEP;
		philo->count++;
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	ft_doing(t_philo *philo, long long time)
{
	while (1)
	{
		ft_annonce(THINK, philo, ft_get_time());
		ft_check_fork(philo);
		time = ft_get_time();
		ft_state(philo, EAT);
		ft_annonce(EAT, philo, time);
		philo->fork[philo->prev].old = philo->philo;
		philo->fork[philo->philo].old = philo->philo;
		usleep(philo->data.time_eat);
		pthread_mutex_unlock(&philo->fork[philo->prev].mutex);
		pthread_mutex_unlock(&philo->fork[philo->philo].mutex);
		time = ft_get_time();
		ft_annonce(SLEEP, philo, time);
		ft_state(philo, SLEEP);
		usleep(philo->data.time_sleep);
	}
}

void	*ft_start(void *philo)
{
	ft_doing((t_philo*)philo, 0);
	pthread_exit(NULL);
}
