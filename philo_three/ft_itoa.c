/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:12:42 by paszhang          #+#    #+#             */
/*   Updated: 2020/02/16 14:53:52 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char		*revers(char *dest)
{
	int		i;
	int		a;
	char	tmp;

	i = 0;
	while (dest[i])
		i++;
	a = 0;
	if (i == 1)
		return (dest);
	i--;
	while (a <= i / 2)
	{
		tmp = dest[i - a];
		dest[i - a] = dest[a];
		dest[a] = tmp;
		a++;
	}
	return (dest);
}

static int		getlenghtitoa(long long n)
{
	int i;

	i = 0;
	while (n >= 0)
	{
		n /= 10;
		i++;
		if (n == 0)
			break ;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			moins;
	char		*dest;
	int			i;
	long long	nbr;

	nbr = n;
	moins = (nbr < 0) ? 1 : 0;
	nbr = (nbr < 0) ? -nbr : nbr;
	i = getlenghtitoa(nbr);
	if (!(dest = malloc(sizeof(char) * (i + moins + 1))))
		return (0);
	i = 0;
	while (nbr >= 0)
	{
		dest[i++] = (nbr % 10) + '0';
		nbr /= 10;
		if (nbr == 0)
			break ;
	}
	if (moins)
		dest[i++] = '-';
	dest[i] = '\0';
	dest = revers(dest);
	return (dest);
}
