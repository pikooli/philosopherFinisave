/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:29:51 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 14:49:27 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_print(t_philo *philo, long long time, char *str)
{
	ft_putnbr(time - philo->timestart);
	ft_putstr("ms ");
	ft_putnbr(philo->philo + 1);
	ft_putstr(str);
}

void		ft_lunch(t_philo *philo, long long time)
{
	ft_putnbr(time - philo->timestart);
	ft_putstr("ms ");
	ft_putnbr(philo->philo + 1);
	ft_putstr(" has taken a fork\n");
	ft_putnbr(time - philo->timestart);
	ft_putstr("ms ");
	ft_putnbr(philo->philo + 1);
	ft_putstr(" is eating\n");
}

void		ft_putcolor(int i)
{
	if (i % 5 == 0)
		ft_putstr("\033[33m");
	else if (i % 5 == 1)
		ft_putstr("\033[35m");
	else if (i % 5 == 2)
		ft_putstr("\033[38m");
	else if (i % 5 == 3)
		ft_putstr("\033[36m");
	else if (i % 5 == 4)
		ft_putstr("\033[37m");
}

void		ft_annonce(int mode, t_philo *philo, long long time)
{
	sem_wait(g_sem);
	ft_putcolor(philo->philo);
	mode == EAT ? ft_lunch(philo, time) : 0;
	mode == SLEEP ? ft_print(philo, time, " is sleeping\n") : 0;
	mode == THINK ? ft_print(philo, time, " is thinking\n") : 0;
	mode == DIED ? ft_print(philo, time, " died\n") : 0;
	mode == SHOW ? ft_print(philo, time, " time\n\n") : 0;
	ft_putstr("\033[0m");
	mode != DIED ? sem_post(g_sem) : 0;
}
