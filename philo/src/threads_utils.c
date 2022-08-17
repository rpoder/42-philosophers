/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:04:38 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 22:05:53 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lauch_threads(t_data *data)
{
	struct timeval	now;
	long long int	starting_at;
	int				ret;

	gettimeofday(&now, NULL);
	starting_at = (now.tv_sec * 1000000) + now.tv_usec + 500000;
	assign_philo_lastmeal(data, starting_at);
	assign_philo_start(data, starting_at);
	ret = pthread_create(&data->death_thread, NULL, &death_routine, data);
	if (ret != 0)
		return (-1);
	pthread_mutex_unlock(&data->go_mutex);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join((data->philos[i].ptr), NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join((data->death_thread), NULL) != 0)
		return (0);
	return (1);
}
