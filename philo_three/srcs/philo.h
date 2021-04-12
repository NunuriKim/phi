/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:43 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:36:45 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# define PROCESS_MAX 200
# define TYPE_FORK 1
# define TYPE_EAT 2
# define TYPE_SLEEP 3
# define TYPE_DIED 4
# define TYPE_SUCCESS 5
# define TYPE_THINK 6

typedef struct		s_philo
{
	int				position;
	sem_t			*hand_on_keyboard;
	sem_t			*m_alarm;
	int				count_eat;
	size_t			start_time;
	size_t			died_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			last_eat_time;
	sem_t			*check_success;
	int				min_count_eat;
}					t_philo;

typedef struct		s_god
{
	sem_t			*m_forks;
	sem_t			*m_alarm;
	int				hungry_die;
	t_philo			philo;
	int				philo_num;
	pthread_t		th_god;
	int				state[PROCESS_MAX];
	sem_t			*check_success[PROCESS_MAX];
	pid_t			pid_philo[PROCESS_MAX];
}					t_god;

int					display_alarm(t_philo *philo, int type);
int					philo_start(t_god *ohgod);

size_t				time_calculator(size_t start_time);
void				waste_time(size_t some_waste_time);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);

void				*call_from_philo(void *data);
int					god_start(t_god *ohgod);
int					free_resource(t_god *ohgod);

#endif
