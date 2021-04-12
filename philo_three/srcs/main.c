/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:57 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:47:35 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					ft_isvalidarg(int argc, char *argv[])
{
	int				i;

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

int					init_check_success(t_god *ohgod)
{
	int				i;
	char			*philo_num;

	i = -1;
	while (++i < ohgod->philo_num)
	{
		philo_num = ft_itoa(i + 1);
		sem_unlink(philo_num);
		ohgod->check_success[i] = sem_open(philo_num, O_CREAT, S_IRWXU, 1);
		free(philo_num);
	}
	return (0);
}

int					args_parse(int argc, char *argv[], t_god *ohgod)
{
	if (argc != 5 && argc != 6 && ft_isvalidarg(argc, argv) == 0)
		return (-1);
	sem_unlink("m_forks");
	sem_unlink("m_alarm");
	ohgod->philo_num = ft_atoi(argv[1]);
	ohgod->philo.died_time = ft_atoi(argv[2]) * 1000;
	ohgod->philo.eat_time = ft_atoi(argv[3]) * 1000;
	ohgod->philo.sleep_time = ft_atoi(argv[4]) * 1000;
	ohgod->philo.start_time = time_calculator(0);
	ohgod->philo.last_eat_time = ohgod->philo.start_time;
	ohgod->philo.min_count_eat = -1;
	if (argc == 6)
		ohgod->philo.min_count_eat = ft_atoi(argv[5]);
	ohgod->philo.count_eat = 0;
	if (ohgod->philo.min_count_eat == -1)
		ohgod->philo.count_eat = -1;
	if ((ohgod->m_forks = sem_open("m_forks", O_CREAT, \
	S_IRWXU, ohgod->philo_num)) == SEM_FAILED)
		return (-1);
	if ((ohgod->m_alarm = sem_open("m_alarm",\
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (-1);
	ohgod->philo.hand_on_keyboard = ohgod->m_forks;
	ohgod->philo.m_alarm = ohgod->m_alarm;
	return (init_check_success(ohgod));
}

int					main(int argc, char *argv[])
{
	int				i;
	t_god			ohgod;

	i = -1;
	ohgod.hungry_die = 0;
	if (args_parse(argc, argv, &ohgod) < 0)
	{
		sem_close(ohgod.m_forks);
		sem_unlink("m_forks");
		sem_close(ohgod.m_alarm);
		sem_unlink("m_alarm");
		return (-1);
	}
	philo_start(&ohgod);
	return (god_start(&ohgod));
}
