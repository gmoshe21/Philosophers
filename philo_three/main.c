/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:53:52 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 18:47:23 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*check_death(void *data)
{
	t_philo			p;
	int				i;

	p = *(t_philo*)data;
	while (1)
	{
		i = 0;
		gettimeofday(&p.new, NULL);
		if ((ft_time(&p)) > p.kill && !p.end_meal)
		{
			sem_wait(p.deaht);
			gettimeofday(&p.check, NULL);
			logs_death(ft_time(&p), p.count + 1, " dead", -1);
			exit(0);
		}
		if (p.plate_noodles == 0)
			exit(0);
		usleep(10);
	}
	return (NULL);
}

void		*streams(t_philo *p)
{
	pthread_t	life;

	pthread_create(&life, NULL, check_death, (void *)p);
	while (p->plate_noodles != 0)
	{
		sem_wait(p->action);
		sem_wait(p->sem);
		sem_wait(p->sem);
		sem_post(p->action);
		gettimeofday(&p->check, NULL);
		logs((ft_oldtime(p)) - p->o_t, p->count + 1, " has taken a fork", -1);
		gettimeofday(&p->check, NULL);
		logs((ft_oldtime(p)) - p->o_t, p->count + 1, " eating", -1);
		gettimeofday(&g_old, NULL);
		usleep(p->time_eat * 1000);
		sem_post(p->sem);
		sem_post(p->sem);
		next(p);
		gettimeofday(&p->check, NULL);
		logs((ft_oldtime(p)) - p->o_t, p->count + 1, " thinking", -1);
		if (p->plate_noodles != -1)
			p->plate_noodles--;
	}
	p->end_meal = 1;
	exit(1);
}

int			running_flow(t_philo *philo)
{
	int		i;
	pid_t	*pid;

	i = -1;
	pid = (pid_t*)malloc(sizeof(pid_t) * (philo->man));
	gettimeofday(&g_old, NULL);
	while (philo->count != philo->man)
	{
		pid[philo->count] = fork();
		if (pid[philo->count] < 0)
			return (1);
		if (pid[philo->count] == 0)
			streams(philo);
		philo->count++;
	}
	ft_exit(philo, pid);
	return (1);
}

int			pars(t_philo *philo, char **data)
{
	philo->man = ft_atoi(data[1]);
	philo->time_eat = ft_atoi(data[3]);
	philo->count = 0;
	philo->time_sleep = ft_atoi(data[4]);
	philo->kill = ft_atoi(data[2]);
	if (philo->man <= 0 || philo->time_eat <= 0 || philo->time_sleep <= 0
	|| philo->kill <= 0)
		return (0);
	philo->plate_noodles = -1;
	philo->end_meal = 0;
	return (1);
}

int			main(int argc, char **argv)
{
	t_philo	p;

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
	p.o_t = p.new.tv_sec * 1000 + p.new.tv_usec / 1000;
	sem_unlink("/semaphor");
	sem_unlink("/act");
	sem_unlink("/print");
	sem_unlink("/deaht");
	p.sem = sem_open("/semaphor", O_CREAT, 0666, p.man);
	p.action = sem_open("/act", O_CREAT, 0666, 1);
	g_print = sem_open("/print", O_CREAT, 0666, 1);
	p.deaht = sem_open("/deaht", O_CREAT, 0666, 1);
	running_flow(&p);
	return (0);
}
