/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:37:33 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:16 by nukim            ###   ########.fr       */
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
	pthread_t	th_philo[MAX_THREAD];

	i = 0;
	while (i < ohgod->philo_num)
	{
		pthread_create(&th_philo[i], 0, go_philo, &ohgod->philo[i]);
		pthread_detach(th_philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < ohgod->philo_num)
	{
		pthread_create(&th_philo[i], 0, go_philo, &ohgod->philo[i]);
		pthread_detach(th_philo[i]);
		i += 2;
	}
	return (0);
}
