/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:39:35 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 18:36:56 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			fork_check(t_philo *philo, int i)
{
	int	fork;

	if (i == 1)
	{
		philo->count--;
		fork = philo->count;
	}
	if (i == 2)
	{
		fork = philo->count + 1;
		if (fork == philo->man)
			fork = 0;
	}
	return (fork);
}

long int	ft_time(t_philo *philo, int f)
{
	long int	i;

	i = ((philo->new.tv_sec - philo->old[f].tv_sec) * 1000) +
	((philo->new.tv_usec - philo->old[f].tv_usec) / 1000);
	return (i);
}

int			ft_oldtime(t_philo *philo, int f)
{
	int	i;

	i = philo->check[f].tv_sec * 1000 + philo->check[f].tv_usec / 1000;
	return (i);
}

void		logs(int time, int philo, char *str)
{
	pthread_mutex_lock(&g_print);
	ft_putnbr_fd(time, 1);
	write(1, "   ", 3);
	ft_putnbr_fd(philo, 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(&g_print);
}

void		next(t_philo *p)
{
	gettimeofday(&p->check[p->count], NULL);
	logs((ft_oldtime(p, p->count)) - g_t, p->count + 1, " philo sleeping");
	usleep((p->time_sleep) * 1000);
}
