/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:21:09 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/15 12:26:36 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo, t_data data, int i, t_fork *fork)
{
	pthread_t tid;

	philo->philo = i;
	philo->fork = fork;
	philo->fork[i].old = -1;
	philo->fork[i].state = -1;
	philo->prev = i == 0 ? data.nb_philo - 1 : i - 1;
	philo->lasteat = ft_get_time();
	philo->state = SLEEP;
	philo->count = 0;
	philo->timestart = ft_get_time();
	philo->data = data;
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_create(&tid, NULL, &ft_start, (void*)philo);
	pthread_detach(tid);
}

t_fork	*ft_fork(t_data data)
{
	t_fork	*fork;
	int		i;

	if (!(fork = malloc(sizeof(t_fork) * data.nb_philo)))
		return (NULL);
	i = -1;
	while (++i < data.nb_philo)
	{
		pthread_mutex_init(&fork[i].mutex, NULL);
		fork[i].old = -1;
		fork[i].state = -1;
	}
	return (fork);
}

void	ft_clean(t_philo *philo)
{
	int i;

	i = -1;
	pthread_mutex_destroy(&g_mutex);
	while (++i < philo->data.nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&philo->fork[i].mutex);
	}
}

void	ft_principal(t_data data)
{
	int		i;
	t_philo	*philo;
	t_fork	*fork;

	if (!(fork = ft_fork(data)))
		return ;
	if (!(philo = malloc(sizeof(t_philo) * data.nb_philo)))
	{
		free(fork);
		return ;
	}
	i = -1;
	while (++i < data.nb_philo)
	{
		ft_init(&philo[i], data, i, fork);
		usleep(50);
	}
	ft_check_state(philo);
	ft_clean(philo);
}

int		main(int ac, char **av)
{
	t_data data;

	if (ac < 5 || ac > 6)
		return (0);
	if (get_arg(&data, ac, av))
		return (0);
	pthread_mutex_init(&g_mutex, NULL);
	ft_principal(data);
	return (0);
}
