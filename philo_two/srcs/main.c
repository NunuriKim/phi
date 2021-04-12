/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:37:39 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:39:39 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_isvalidarg(int argc, char *argv[])
{
	int			i;

	i = 0;
	while (i < argc)
	{
		if (*argv[i] == 0)
			return (0);
		while (*argv[i] && *argv[i] >= '0' && *argv[i] <= '9')
			argv[i]++;
		if (*argv[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int				args_parse(int argc, char *argv[], t_god *ohgod)
{
	if (argc != 5 && argc != 6 && ft_isvalidarg(argc, argv) == 0)
		return (-1);
	sem_unlink("m_forks");
	sem_unlink("m_alarm");
	ohgod->philo_num = ft_atoi(argv[1]);
	ohgod->died_time = ft_atoi(argv[2]) * 1000;
	ohgod->eat_time = ft_atoi(argv[3]) * 1000;
	ohgod->sleep_time = ft_atoi(argv[4]) * 1000;
	ohgod->start_time = time_calculator(0);
	ohgod->min_count_eat = -1;
	ohgod->angel_work = ohgod->philo_num;
	if (argc == 6)
		ohgod->min_count_eat = ft_atoi(argv[5]);
	if ((ohgod->m_forks = sem_open("m_forks", O_CREAT, \
	S_IRWXU, ohgod->philo_num)) == SEM_FAILED)
		return (-1);
	if ((ohgod->m_alarm = sem_open("m_alarm",\
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

void			philo_orientation(t_god *ohgod)
{
	int			i;

	i = 0;
	while (i < ohgod->philo_num)
	{
		ohgod->philo[i].position = i + 1;
		ohgod->philo[i].count_eat = 0;
		if (ohgod->min_count_eat == -1)
			ohgod->philo[i].count_eat = -1;
		ohgod->philo[i].died_time = ohgod->died_time;
		ohgod->philo[i].eat_time = ohgod->eat_time;
		ohgod->philo[i].sleep_time = ohgod->sleep_time;
		ohgod->philo[i].start_time = ohgod->start_time;
		ohgod->philo[i].last_eat_time = ohgod->start_time;
		ohgod->philo[i].hand_on_keyboard = ohgod->m_forks;
		ohgod->philo[i].m_alarm = ohgod->m_alarm;
		i++;
	}
}

int				main(int argc, char *argv[])
{
	int			i;
	t_god		ohgod;

	i = -1;
	if (args_parse(argc, argv, &ohgod) < 0)
	{
		sem_close(ohgod.m_forks);
		sem_unlink("m_forks");
		sem_close(ohgod.m_alarm);
		sem_unlink("m_alarm");
		return (-1);
	}
	philo_orientation(&ohgod);
	philo_start(&ohgod);
	return (god_start(&ohgod));
}
