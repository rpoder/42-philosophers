/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:51:34 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 17:56:32 by rpoder           ###   ########.fr       */
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

static bool	check_death(t_data *data, int i)

void	*death_routine(void *arg)
{
	bool			alive;
	int				i;
	struct timeval	now;
	long long int	now_int;
	t_data			*data;
	int				finito;

	data = (t_data *)arg;
	alive = true;
	while (i < data->philo_nb && alive)
	{
		finito = 0;
		i = 0;
		gettimeofday(&now, NULL);
		now_int = (now.tv_sec * 1000000) + now.tv_usec;
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		if ((now_int - data->philos[i].last_meal) > data->t_die && !data->philos[i].finish)
		{
			alive = false;
			print_status(MSG_DIE, &data->philos[i]);
			pthread_mutex_lock(&data->is_dead_mutex);
			data->is_dead = i + 1;
			pthread_mutex_unlock(&data->is_dead_mutex);
		}
		else if (data->philos[i].finish)
			finito++;
		if (finito == data->philo_nb)
			alive = false;
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		usleep(100);
		i++;
	}
	return (NULL);
}
