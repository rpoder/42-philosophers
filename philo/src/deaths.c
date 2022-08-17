/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:51:34 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 19:32:53 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->is_dead_mutex);
	if (data->is_dead)
	{
		pthread_mutex_unlock(&data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->is_dead_mutex);
	return (0);
}

static bool	assign_death(t_data *data, int i)
{
	print_status(MSG_DIE, &data->philos[i]);
	pthread_mutex_lock(&data->is_dead_mutex);
	data->is_dead = i + 1;
	pthread_mutex_unlock(&data->is_dead_mutex);
	return (false);
}

static bool	while_death(t_data *data, bool alive)
{
	int				i;
	int				finito;
	struct timeval	now;

	i = 0;
	finito = 0;
	while (i < data->philo_nb && alive)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		pthread_mutex_lock(&data->philos[i].finish_mutex);
		if ((((now.tv_sec * 1000000) + now.tv_usec) - data->philos[i].last_meal)
			> data->t_die && !data->philos[i].finish)
			alive = assign_death(data, i);
		else if (data->philos[i].finish)
			finito++;
		if (finito == data->philo_nb)
			alive = false;
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		pthread_mutex_unlock(&data->philos[i].finish_mutex);
		usleep(100);
		i++;
	}
	return (alive);
}

void	*death_routine(void *arg)
{
	bool			alive;
	struct timeval	now;
	t_data			*data;

	data = (t_data *)arg;
	alive = true;
	while (alive)
		alive = while_death(data, alive);
	return (NULL);
}
