/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:37:12 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:48:38 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			*call_from_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	while (1)
	{
		if (philo->died_time < time_calculator(philo->last_eat_time))
		{
			display_alarm(philo, TYPE_DIED);
			exit(TYPE_DIED);
		}
		if (philo->count_eat >= 0 && \
		philo->count_eat >= philo->min_count_eat)
		{
			sem_post(philo->check_success);
			philo->count_eat = -1;
		}
		usleep(100);
	}
	return (0);
}

void			*send_end_lunch(void *data)
{
	int			i;
	t_god		*ohgod;

	i = -1;
	ohgod = data;
	while (++i < ohgod->philo_num)
		sem_wait(ohgod->check_success[i]);
	if (ohgod->hungry_die)
		return (0);
	display_alarm(&ohgod->philo, TYPE_SUCCESS);
	i = -1;
	while (++i < ohgod->philo_num)
		kill(ohgod->pid_philo[i], SIGKILL);
	free_resource(ohgod);
	exit(0);
	return (0);
}

int				free_resource(t_god *ohgod)
{
	int			i;
	char		*philo_num;

	i = -1;
	if (ohgod->philo.m_alarm)
	{
		sem_close(ohgod->philo.m_alarm);
		sem_unlink("m_alarm");
	}
	if (ohgod->philo.hand_on_keyboard)
	{
		sem_close(ohgod->philo.hand_on_keyboard);
		sem_unlink("m_forks");
	}
	if (*ohgod->check_success)
		while (++i < ohgod->philo_num)
		{
			philo_num = ft_itoa(i + 1);
			sem_post(ohgod->check_success[i]);
			sem_close(ohgod->check_success[i]);
			sem_unlink(philo_num);
			free(philo_num);
		}
	return (0);
}

int				god_start(t_god *ohgod)
{
	int			i;
	pthread_t	end_lunch;

	i = 0;
	usleep(200);
	pthread_create(&end_lunch, 0, send_end_lunch, ohgod);
	pthread_detach(end_lunch);
	while (1)
	{
		if (waitpid(ohgod->pid_philo[i], &ohgod->state[i], \
		WNOHANG | WCONTINUED | WUNTRACED))
		{
			if (WEXITSTATUS(ohgod->state[i]) == TYPE_DIED)
			{
				ohgod->hungry_die = 1;
				i = -1;
				while (++i < ohgod->philo_num)
					kill(ohgod->pid_philo[i], SIGKILL);
				free_resource(ohgod);
				return (0);
			}
		}
		i = i == ohgod->philo_num - 1 ? 0 : i + 1;
	}
	return (0);
}
