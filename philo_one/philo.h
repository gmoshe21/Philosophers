/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:56:04 by gmoshe            #+#    #+#             */
/*   Updated: 2020/12/14 17:48:59 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

int				g_t;
pthread_mutex_t	g_print;

typedef struct	s_philo
{
	struct timeval	*check;
	struct timeval	*old;
	struct timeval	new;
	int				man;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				count;
	int				kill;
	int				plate_noodles;
	int				*end_meal;
	pthread_mutex_t	*mutex_p;
	pthread_t		*pot;
}				t_philo;

int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			logs(int time, int philo, char *str);
int				ft_oldtime(t_philo *philo, int f);
long int		ft_time(t_philo *philo, int f);
int				fork_check(t_philo *philo, int i);
int				ft_check(t_philo *philo, int i, int j);
void			next(t_philo *p);

#endif
