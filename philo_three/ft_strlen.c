/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:53:28 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 18:45:36 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void		ft_exit(t_philo *philo, pid_t *pid)
{
	int	i;

	i = 0;
	waitpid(-1, &i, WUNTRACED);
	if (i != 0)
	{
		i = 1;
		while (i != philo->man)
		{
			waitpid(-1, NULL, WUNTRACED);
			i++;
		}
	}
	else
	{
		i = -1;
		while (++i < philo->count)
			kill(pid[i], 0);
	}
}

void		next(t_philo *p)
{
	gettimeofday(&p->check, NULL);
	logs((ft_oldtime(p)) - p->o_t, p->count + 1, " sleeping", -1);
	usleep((p->time_sleep) * 1000);
}
