/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:01:33 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 20:51:21 by rpoder           ###   ########.fr       */
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
	data->t_sleep = ft_atoi(args[2]) * 1000;
	data->t_eat = ft_atoi(args[3]) * 1000;
	if (args[4])
		data->must_eat = ft_atoi(args[4]) * 1000;
	else
		data->must_eat = -1;
	if (!create_mutexes(data))
		return (0);
	pthread_mutex_lock(&data->go_mutex);
	if (!create_chopsticks(data))
	{
		free(data);
		return (0);
	}
	if (!create_philos(data))
		return (0);
	if (!create_threads(data))
		return (0);
	return (data);
}

int	create_chopsticks(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo_nb <= 0)
		return (0);
	data->chopsticks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->chopsticks)
		return (0);
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->chopsticks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo_nb <= 0)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (0);
	while (i < data->philo_nb)
	{
		data->philos[i].tid = i + 1;
		data->philos[i].left = i;
		data->philos[i].right = i + 1;
		if (i == data->philo_nb - 1)
			data->philos[i].right = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
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
			return (0);
		i = i + 2;
	}
	i = 1;
	usleep(data->t_eat - 500);
	while (i < data->philo_nb)
	{
		ret = pthread_create(&data->philos[i].ptr, NULL, &routine, &data->philos[i]);
		if (ret != 0)
			return (0);
		i = i + 2;
	}
	return (1);
}

int	create_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->go_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	return (1);
}
