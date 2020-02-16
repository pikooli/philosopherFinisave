/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:21:09 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 14:56:37 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo, t_data data, int i, t_fork *forkstruct)
{
	char *str;

	str = ft_strjoin("philo", ft_itoa(i));
	philo->philo = i;
	philo->fork = forkstruct;
	philo->fork[i].old = -1;
	philo->fork[i].state = -1;
	philo->prev = i == 0 ? data.nb_philo - 1 : i - 1;
	philo->lasteat = ft_get_time();
	philo->state = SLEEP;
	philo->count = 0;
	philo->timestart = ft_get_time();
	philo->data = data;
	philo->str = str;
	sem_unlink(str);
	philo->sem = sem_open(str, O_CREAT, 0644, 1);
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
		fork[i].count = 0;
		fork[i].sem = sem;
		fork[i].old = -1;
		fork[i].state = -1;
	}
	return (fork);
}

int		ft_fork2(t_philo *philo)
{
	int			i;
	pthread_t	tid;

	i = -1;
	while (++i < philo[0].data.nb_philo)
		if ((philo[i].pid = fork()) == 0)
		{
			pthread_create(&tid, NULL, &ft_start, (void*)&philo[i]);
			pthread_detach(tid);
			ft_check_state(&philo[i]);
			return (1);
		}
	return (0);
}

void	ft_principal(t_data data)
{
	int		i;
	t_philo	*philo;
	t_fork	*fork;
	sem_t	*sem2;

	sem_unlink("g_dead");
	if ((g_dead = sem_open("g_dead", O_CREAT, 0644, 0)) == SEM_FAILED)
		return ;
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
		ft_init(&philo[i], data, i, fork);
	if (ft_fork2(philo))
		return ;
	sem_wait(g_dead);
	ft_clean(philo);
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
