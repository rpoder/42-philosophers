/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:47:21 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 18:21:51 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* void	unlock_mutexes(t_data *data)
{
	int	i;
	int	dead;

	i = 0;
	pthread_mutex_lock(&data->is_dead_mutex);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->is_dead_mutex);
	while (i < data->philo_nb)
	{
		pthread_mutex_unlock(&data->chopsticks[i]);
		i++;
	}
} */

void	*ft_free(t_data *data, int status)
{
	if (status == 1)
		free(data);
	if (status == 2)
	{
		destroy_data_mutexes(data);
		free(data);
	}
	if (status == 3)
	{
		destroy_data_mutexes(data);
		destroy_chopsticks_mutexes(data);
		free(data);
	}
	if (status == 4)
	{
		pthread_mutex_unlock(&data->go_mutex);
		destroy_data_mutexes(data);
		destroy_chopsticks_mutexes(data);
		free(data);
	}
	return (NULL);
}

void	free_all(t_data *data)
{
	destroy_mutexes(data);
	free(data->philos);
	free(data);
}
