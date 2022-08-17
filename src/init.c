/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:01:33 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 12:43:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*init_data(char **args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_nb = ft_atoi(args[0]);
	data->t_die = ft_atoi(args[1]) * 1000;
	data->t_eat = ft_atoi(args[2]) * 1000;
	data->t_sleep = ft_atoi(args[3]) * 1000;
	if (args[4])
		data->must_eat = ft_atoi(args[4]);
	else
		data->must_eat = -1;
	data->is_dead = 0;
	if (create_data_mutexes(data) != 0)
	{
		free(data);
		return (NULL);
	}
	if (create_chopsticks(data) != 0)
	{
		destroy_data_mutexes(data);
		free(data);
		return (NULL);
	}
	if (create_philos(data) != 0)
	{
		destroy_data_mutexes(data);
		destroy_chopsticks_mutexes(data);
		free(data);
		return (NULL);
	}
	pthread_mutex_lock(&data->go_mutex);
	if (create_threads(data) != 0)
	{
		pthread_mutex_unlock(&data->go_mutex);
		destroy_data_mutexes(data);
		destroy_chopsticks_mutexes(data);
		free(data);
		return (NULL);
	}
	return (data);
}

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
		ret = pthread_create(&data->philos[i].ptr, NULL, &routine, &data->philos[i]);
		if (ret != 0)
			return (-1);
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
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
