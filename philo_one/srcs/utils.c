/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nukim <nukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:33 by nukim             #+#    #+#             */
/*   Updated: 2021/04/13 03:39:39 by nukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t				time_calculator(size_t start_time)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000000 + current.tv_usec - start_time);
}

void				waste_time(size_t some_waste_time)
{
	size_t			start_time;

	start_time = time_calculator(0);
	while (time_calculator(0) < start_time + some_waste_time)
		;
}

int					ft_atoi(const char *str)
{
	long long		result;
	int				i;
	int				sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
