/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:39:35 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 14:46:10 by gmoshe           ###   ########.fr       */
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

long int	ft_time(t_philo *philo)
{
	long int	i;

	i = ((philo->new.tv_sec - g_old.tv_sec) * 1000) +
	((philo->new.tv_usec - g_old.tv_usec) / 1000);
	return (i);
}

int			ft_oldtime(t_philo *philo)
{
	int	i;

	i = philo->check.tv_sec * 1000 + philo->check.tv_usec / 1000;
	return (i);
}

void		logs(int time, int philo, char *str, int vil)
{
	sem_wait(g_print);
	ft_putnbr_fd(time, 1);
	write(1, "   ", 3);
	ft_putnbr_fd(philo, 1);
	write(1, str, ft_strlen(str));
	if (vil != -1)
		ft_putnbr_fd(vil, 1);
	write(1, "\n", 1);
	sem_post(g_print);
}

void		logs_death(int time, int philo, char *str, int vil)
{
	sem_wait(g_print);
	ft_putnbr_fd(time, 1);
	write(1, "   ", 3);
	ft_putnbr_fd(philo, 1);
	write(1, str, ft_strlen(str));
	if (vil != -1)
		ft_putnbr_fd(vil, 1);
	write(1, "\n", 1);
}
