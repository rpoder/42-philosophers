/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:01:33 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 18:26:08 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_data_values(t_data *data, char **args)
{
	data->philo_nb = ft_atoi(args[0]);
	data->t_die = ft_atol(args[1]) * 1000;
	data->t_eat = ft_atol(args[2]) * 1000;
	data->t_sleep = ft_atol(args[3]) * 1000;
	if (args[4])
		data->must_eat = ft_atoi(args[4]);
	else
		data->must_eat = -1;
	data->is_dead = 0;
}

t_data	*init_data(char **args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	assign_data_values(data, args);
	if (create_data_mutexes(data) != 0)
		return (ft_free(data, 1));
	if (create_chopsticks(data) != 0)
		return (ft_free(data, 2));
	if (create_philos(data) != 0)
		return (ft_free(data, 3));
	pthread_mutex_lock(&data->go_mutex);
	if (create_threads(data) != 0)
		return (ft_free(data, 4));
	return (data);
}
