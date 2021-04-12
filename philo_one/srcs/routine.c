/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:03 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:57 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->m_l_hand);
	display_alarm(philo, TYPE_FORK);
	pthread_mutex_lock(philo->m_r_hand);
	display_alarm(philo, TYPE_FORK);
	display_alarm(philo, TYPE_EAT);
	philo->last_eat_time = time_calculator(0);
	waste_time(philo->eat_time);
	if (philo->count_eat >= 0)
		philo->count_eat++;
	pthread_mutex_unlock(philo->m_l_hand);
	pthread_mutex_unlock(philo->m_r_hand);
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
	usleep(100);
	i = 1;
	while (i < ohgod->philo_num)
	{
		pthread_create(&th_philo[i], 0, go_philo, &ohgod->philo[i]);
		pthread_detach(th_philo[i]);
		i += 2;
	}
	return (0);
}
