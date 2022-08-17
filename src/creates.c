/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:12:51 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 19:39:11 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_chopsticks(t_data *data)
{
	int	i;

	i = 0;
	data->chopsticks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->chopsticks)
		return (-1);
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->chopsticks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (-1);
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].tid = i + 1;
		data->philos[i].left = i;
		data->philos[i].right = i + 1;
		if (i == data->philo_nb - 1)
			data->philos[i].right = 0;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].finish = false;
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->philo_nb)
	{
		ret = pthread_create(&data->philos[i].ptr, NULL,
				&routine, &data->philos[i]);
		if (ret != 0)
			return (-1);
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&data->philos[i].finish_mutex, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_data_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->go_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->is_dead_mutex, NULL) != 0)
		return (-1);
	return (0);
}
