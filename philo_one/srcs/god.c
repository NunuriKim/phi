/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:20 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:50 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					display_alarm(t_philo *philo, int type)
{
	pthread_mutex_lock(philo->m_alarm);
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
		printf(" %d is thinking\n", philo->position);
	else if (type == TYPE_DIED)
	{
		printf(" %d is died\n", philo->position);
		return (1);
	}
	pthread_mutex_unlock(philo->m_alarm);
	return (0);
}

void				*god_check(void *data)
{
	t_god			*ohgod;
	t_philo			*philo;
	int				i;

	ohgod = data;
	i = 0;
	while (1)
	{
		philo = &ohgod->philo[i];
		if (ohgod->died_time < time_calculator(philo->last_eat_time))
			if (display_alarm(philo, TYPE_DIED))
				break ;
		if (philo->count_eat >= 0 && \
		philo->count_eat >= ohgod->min_count_eat)
		{
			ohgod->angel_work--;
			philo->count_eat = -MAX_THREAD;
		}
		if (!ohgod->angel_work)
			if (display_alarm(philo, TYPE_SUCCESS))
				break ;
		i = i == ohgod->philo_num - 1 ? 0 : i + 1;
		usleep(100);
	}
	return (0);
}

int					god_start(t_god *ohgod)
{
	if (pthread_create(&ohgod->th_god, 0, god_check, ohgod))
		return (-1);
	if (pthread_join(ohgod->th_god, 0))
		return (-1);
	else
		return (0);
}
