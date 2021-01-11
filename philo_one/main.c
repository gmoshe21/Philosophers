/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:53:52 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 18:46:49 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*check_death(void *data)
{
	t_philo			p;
	int				i[2];

	p = *(t_philo*)data;
	while (1)
	{
		i[0] = -1;
		i[1] = 0;
		gettimeofday(&p.new, NULL);
		while (++i[0] != p.man)
		{
			if ((ft_time(&p, i[0])) - 1 > p.kill && !p.end_meal[i[0]])
			{
				gettimeofday(&p.check[i[0]], NULL);
				logs((ft_oldtime(&p, i[0])) - g_t, i[0] + 1, " dead");
				pthread_mutex_lock(&g_print);
				return (NULL);
			}
			i[1] = ft_check(&p, i[0], i[1]);
		}
		if (i[1] == p.man)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}

void		*streams(void *data)
{
	t_philo	p;
	int		frk[2];

	p = *(t_philo*)data;
	frk[0] = fork_check(&p, 1);
	frk[1] = fork_check(&p, 2);
	while (p.plate_noodles != 0)
	{
		pthread_mutex_lock(&p.mutex_p[frk[0]]);
		pthread_mutex_lock(&p.mutex_p[frk[1]]);
		gettimeofday(&p.check[p.count], NULL);
		logs((ft_oldtime(&p, p.count)) - g_t, p.count + 1, " has taken a fork");
		logs((ft_oldtime(&p, p.count)) - g_t, p.count + 1, " eating");
		gettimeofday(&p.old[p.count], NULL);
		usleep(p.time_eat * 1000);
		pthread_mutex_unlock(&p.mutex_p[frk[0]]);
		pthread_mutex_unlock(&p.mutex_p[frk[1]]);
		next(&p);
		gettimeofday(&p.check[p.count], NULL);
		logs((ft_oldtime(&p, p.count)) - g_t, p.count + 1, " thinking");
		if (p.plate_noodles != -1)
			p.plate_noodles--;
	}
	p.end_meal[p.count] = 1;
	return (NULL);
}

int			running_flow(t_philo *philo)
{
	int	i;

	i = 0;
	philo->pot = (pthread_t*)malloc(sizeof(pthread_t) * (philo->man + 1));
	while (i != philo->man)
		gettimeofday(&philo->old[i++], NULL);
	while (philo->count != philo->man)
	{
		pthread_create(&philo->pot[philo->count], NULL, streams, (void *)philo);
		philo->count++;
		usleep(10);
	}
	while (1)
	{
		pthread_create(&philo->pot[philo->man], NULL,
		check_death, (void *)philo);
		pthread_join(philo->pot[philo->man], NULL);
		return (0);
	}
	return (1);
}

int			pars(t_philo *philo, char **data)
{
	int	i;

	i = 0;
	philo->man = ft_atoi(data[1]);
	philo->time_eat = ft_atoi(data[3]);
	philo->count = 0;
	philo->time_sleep = ft_atoi(data[4]);
	philo->kill = ft_atoi(data[2]);
	if (philo->man <= 0 || philo->time_eat <= 0 || philo->time_sleep <= 0
	|| philo->kill <= 0)
		return (0);
	philo->plate_noodles = -1;
	if (!(philo->end_meal = (int*)malloc(sizeof(int) * philo->man)))
		return (0);
	while (i != philo->man)
		philo->end_meal[i++] = 0;
	return (1);
}

int			main(int argc, char **argv)
{
	t_philo	p;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	if (!(pars(&p, argv)))
		return (write(1, "Error\n", 6));
	if (argc == 6)
	{
		p.plate_noodles = ft_atoi(argv[5]);
		if (p.plate_noodles < 0)
			return (write(1, "Error\n", 6));
	}
	gettimeofday(&p.new, NULL);
	g_t = p.new.tv_sec * 1000 + p.new.tv_usec / 1000;
	p.mutex_p = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * (p.man));
	p.old = malloc(p.man);
	p.check = malloc(p.man);
	while (i != p.man)
		pthread_mutex_init(&p.mutex_p[i++], NULL);
	pthread_mutex_init(&g_print, NULL);
	running_flow(&p);
	return (0);
}
