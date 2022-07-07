/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 18:24:25 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lauch_threads(t_data *data)
{
	struct			 timeval now;
	long long int	starting_at;

	gettimeofday(&now, NULL);
	starting_at = (now.tv_sec * 1000000) + now.tv_usec + 500000;
	assign_philo_lastmeal(data);
	assign_philo_start(data, starting_at);
	pthread_mutex_unlock(&data->go_mutex);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	long long int	time;
	struct timeval	now;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->data->go_mutex);
	pthread_mutex_unlock(&philo->data->go_mutex);
	while (1)
	{
		gettimeofday(&now, NULL);
		time = (now.tv_sec * 1000000) + now.tv_usec;
		if ( time >= philo->start)
			break;
	}
	//ft_putstr_fd("coucou\n", 1);
	print_status(1, philo->start, philo->tid);
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join((data->philos[i].ptr),NULL) != 0)
			return (0);
		i++;
	}
	// if (pthread_join((data->death_thread),NULL) != 0)
	// 		return (0);
	return (1);
}
