/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:56:04 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 18:05:32 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <stdlib.h>

sem_t			*g_print;
struct timeval	g_old;

typedef struct	s_philo
{
	struct timeval	check;
	struct timeval	new;
	int				man;
	int				o_t;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				count;
	int				kill;
	int				plate_noodles;
	int				end_meal;
	sem_t			*deaht;
	sem_t			*sem;
	sem_t			*action;
	pthread_t		*pot;
}				t_philo;

void			logs(int time, int philo, char *str, int vil);
int				ft_oldtime(t_philo *philo);
long int		ft_time(t_philo *philo);
int				fork_check(t_philo *philo, int i);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			logs_death(int time, int philo, char *str, int vil);
void			ft_exit(t_philo *philo, pid_t *pid);
void			next(t_philo *p);

#endif
