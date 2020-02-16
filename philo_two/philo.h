/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:19:50 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/15 15:01:06 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <semaphore.h>

enum				e_etat {EAT, ALIVE, WAKE, HUNGRY, TAKE
	, SHOW, SLEEP, THINK, DIED, PUTDOWN};

sem_t				*g_sem;
sem_t				*g_sem2;

typedef struct		s_data
{
	long long		nb_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		nb_eat;
}					t_data;

typedef struct		s_fork
{
	sem_t			*sem;
	long long		old;
	int				state;
}					t_fork;

typedef struct		s_philo
{
	long long		philo;
	t_fork			*fork;
	long long		prev;
	long long		lasteat;
	long long		state;
	t_data			data;
	long long		count;
	long long		timestart;
	sem_t			*sem;
}					t_philo;

void				ft_putstr(char *str);
void				ft_putnbr(long long nbr);
long long			ft_atoi(char *str);
int					get_arg(t_data *g_data, int ac, char **av);
void				ft_print(t_philo *philo, long long time, char *str);
void				ft_annonce(int mode, t_philo *philo, long long time);
void				*ft_start(void *philo);
long long			ft_get_time();
int					ft_check_state(t_philo *philo);
#endif
