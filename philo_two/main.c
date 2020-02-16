/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:21:09 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 10:58:07 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo, t_data data, int i, t_fork *fork)
{
	pthread_t	tid;

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
	philo->sem = sem_open("philo", O_CREAT, 0644, 1);
	sem_unlink("philo");
	pthread_create(&tid, NULL, &ft_start, (void*)philo);
	pthread_detach(tid);
}

t_fork	*ft_fork(t_data data, sem_t *sem)
{
	t_fork	*fork;
	int		i;

	if (!(fork = malloc(sizeof(t_fork) * data.nb_philo)))
		return (NULL);
	i = -1;
	while (++i < data.nb_philo)
	{
		fork[i].sem = sem;
		fork[i].old = -1;
		fork[i].state = -1;
	}
	return (fork);
}

void	ft_clean(void)
{
	sem_unlink("g_sem");
	sem_unlink("g_sem2");
	sem_unlink("sem");
}

void	ft_principal(t_data data)
{
	int		i;
	t_philo	*philo;
	t_fork	*fork;
	sem_t	*sem2;

	sem_unlink("sem");
	if ((sem2 = sem_open("sem", O_CREAT, 0644, data.nb_philo)) == SEM_FAILED)
		return ;
	if (!(fork = ft_fork(data, sem2)))
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
		usleep(10);
	}
	ft_check_state(philo);
	ft_clean();
	free(philo->fork);
	free(philo);
}

int		main(int ac, char **av)
{
	t_data data;

	if (ac < 5 || ac > 6)
		return (0);
	if (get_arg(&data, ac, av))
		return (0);
	sem_unlink("g_sem");
	if ((g_sem = sem_open("g_sem", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (0);
	sem_unlink("g_sem2");
	if ((g_sem2 = sem_open("g_sem2", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (0);
	ft_principal(data);
	return (0);
}
