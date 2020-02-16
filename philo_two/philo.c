/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:24:16 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/15 15:04:26 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_check_fork(t_philo *philo)
{
	sem_wait(g_sem2);
	sem_wait(philo->fork->sem);
	sem_wait(philo->fork->sem);
	sem_post(g_sem2);
	return (0);
}

void	ft_state(t_philo *philo, int state)
{
	if (state == EAT)
	{
		sem_wait(philo->sem);
		philo->state = EAT;
		philo->lasteat = ft_get_time();
		sem_post(philo->sem);
	}
	if (state == SLEEP)
	{
		sem_wait(philo->sem);
		philo->state = SLEEP;
		philo->count++;
		sem_post(philo->sem);
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
		usleep(philo->data.time_eat);
		sem_post(philo->fork->sem);
		sem_post(philo->fork->sem);
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
