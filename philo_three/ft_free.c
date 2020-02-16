/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:53:06 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 14:53:16 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_clean(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo[0].data.nb_philo)
		kill(philo[i].pid, SIGKILL);
	sem_unlink("g_sem");
	sem_unlink("g_sem2");
	sem_unlink("sem");
	free(philo->fork);
	free(philo);
}
