/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:35:54 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:38:35 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_THREAD 200
# define TYPE_FORK 1
# define TYPE_EAT 2
# define TYPE_SLEEP 3
# define TYPE_DIED 4
# define TYPE_SUCCESS 5
# define TYPE_THINK 6

typedef struct		s_philo
{
	int				position;
	pthread_mutex_t	*m_r_hand;
	pthread_mutex_t	*m_l_hand;
	pthread_mutex_t	*m_alarm;
	int				count_eat;
	size_t			start_time;
	size_t			died_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			last_eat_time;
}					t_philo;

typedef struct		s_god
{
	pthread_mutex_t	m_forks[MAX_THREAD];
	pthread_mutex_t	m_alarm;
	t_philo			philo[MAX_THREAD];
	int				philo_num;
	int				angel_work;
	size_t			start_time;
	size_t			died_time;
	size_t			eat_time;
	size_t			sleep_time;
	int				min_count_eat;
	pthread_t		th_god;
}					t_god;

void				philo_routine(t_philo *philo);
void				*go_philo(void *data);
int					philo_start(t_god *ohgod);

size_t				time_calculator(size_t start_time);
void				waste_time(size_t some_waste_time);
int					ft_atoi(const char *str);

int					display_alarm(t_philo *philo, int type);
void				*god_check(void *data);
int					god_start(t_god *ohgod);

#endif
