/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:50 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:12 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				display_alarm(t_philo *philo, int type)
{
	sem_wait(philo->m_alarm);
	if (type == TYPE_SUCCESS)
	{
		printf("everybody eat count success\n");
		return (1);
	}
	printf("%lums", time_calculator(philo->start_time) / 1000);
	if (type == TYPE_SUCCESS)
		return (TYPE_SUCCESS);
	else if (type == TYPE_FORK)
		printf(" %d has taken a fork\n", philo->position);
	else if (type == TYPE_EAT)
		printf(" %d is eating\n", philo->position);
	else if (type == TYPE_SLEEP)
		printf(" %d is sleeping\n", philo->position);
	else if (type == TYPE_THINK)
		printf(" %d is in thinking\n", philo->position);
	else if (type == TYPE_DIED)
	{
		printf(" %d is died\n", philo->position);
		return (1);
	}
	sem_post(philo->m_alarm);
	return (0);
}

void			philo_routine(t_philo *philo)
{
	sem_wait(philo->hand_on_keyboard);
	display_alarm(philo, TYPE_FORK);
	sem_wait(philo->hand_on_keyboard);
	display_alarm(philo, TYPE_FORK);
	display_alarm(philo, TYPE_EAT);
	philo->last_eat_time = time_calculator(0);
	waste_time(philo->eat_time);
	if (philo->count_eat >= 0)
		philo->count_eat++;
	sem_post(philo->hand_on_keyboard);
	sem_post(philo->hand_on_keyboard);
	display_alarm(philo, TYPE_SLEEP);
	waste_time(philo->sleep_time);
	display_alarm(philo, TYPE_THINK);
}

void			*go_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
		philo_routine(philo);
}

int				philo_start(t_god *ohgod)
{
	int			i;
	pthread_t	th_god_start;

	i = -1;
	while (++i < ohgod->philo_num)
	{
		ohgod->philo.check_success = ohgod->check_success[i];
		ohgod->pid_philo[i] = fork();
		if (ohgod->pid_philo[i] == 0)
		{
			sem_wait(ohgod->philo.check_success);
			ohgod->philo.position = i + 1;
			pthread_create(&th_god_start, 0,\
			call_from_philo, &ohgod->philo);
			pthread_detach(th_god_start);
			go_philo(&ohgod->philo);
		}
		else
			usleep(100);
	}
	if (ohgod->pid_philo[0])
		god_start(ohgod);
	return (0);
}
