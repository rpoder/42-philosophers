/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:47:21 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/15 18:47:39 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:24:36 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/05 16:50:36 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	unlock_mutexes(t_data *data)
{
	int	i;
	int	dead;

	i = 0;
	pthread_mutex_lock(&data->is_dead_mutex);
	dead = data->is_dead;
	//printf("%d IS FUCKING DEAD\n\n\n", dead);
	pthread_mutex_unlock(&data->is_dead_mutex);
	while (i < data->philo_nb)
	{
		if (i + 1 != dead)
			pthread_mutex_unlock(&data->chopsticks[i]);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
//	unlock_mutexes(data);
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->chopsticks[i]);
		i++;
	}
	free (data->chopsticks);
	pthread_mutex_destroy(&data->print_mutex);

}

void	free_all(t_data *data)
{
	//destroy_mutexes(data);
	free(data->philos);
	free(data);
}
