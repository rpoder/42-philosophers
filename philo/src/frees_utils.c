/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:47:21 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 19:34:10 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_data_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->go_mutex);
	pthread_mutex_destroy(&data->is_dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

void	destroy_last_meal_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->philos[i].finish_mutex);
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		i++;
	}
}

void	destroy_chopsticks_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->chopsticks[i]);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	destroy_last_meal_mutexes(data);
	destroy_chopsticks_mutexes(data);
	free (data->chopsticks);
	destroy_data_mutexes(data);
}
