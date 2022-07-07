/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:37:46 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 18:10:03 by rpoder           ###   ########.fr       */
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

void	assign_philo_lastmeal(t_data *data)
{
	int	i;
	struct timeval	now;
	long long int	last_meal;

	i = 0;
	gettimeofday(&now, NULL);
	last_meal = (now.tv_sec * 1000000) + now.tv_usec;
	while (i < data->philo_nb)
	{
		data->philos[i].last_meal = last_meal;
		i++;
	}
}
