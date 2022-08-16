/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/16 16:24:48 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lauch_threads(t_data *data)
{
	struct			 timeval now;
	long long int	starting_at;
	int	ret;

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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->go_mutex);
	pthread_mutex_unlock(&philo->data->go_mutex);
	wait_till_time(philo->start);
	if (philo->tid % 2 == 0)
	{
		print_status(MSG_THINKING, philo);
		usleep(philo->data->t_eat / 4);
	}
	while (!is_dead(philo->data))
	{
		wait_and_take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
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
	if (pthread_join((data->death_thread),NULL) != 0)
			return (0);
	return (1);
}
