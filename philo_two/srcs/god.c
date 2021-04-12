/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:37:45 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:20 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
