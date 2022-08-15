/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:37:46 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/15 18:05:11 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_philo_start(t_data *data, long long int start)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].start = start;
		i++;
	}
}

void	assign_philo_lastmeal(t_data *data, long long int last_meal)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		data->philos[i].last_meal = last_meal;
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		i++;
	}
}

void	wait_till_time(long long int time)
{
	long long int	now_int;
	struct timeval	now;
	while (1)
	{
		gettimeofday(&now, NULL);
		now_int = (now.tv_sec * 1000000) + now.tv_usec;
		if (now_int >= time)
			break;
	}
}
