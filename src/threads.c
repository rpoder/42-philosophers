/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 16:01:50 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	has_eaten_enough(t_philo *philo)
{
	if (philo->data->must_eat == -1)
		return (0);
	if (philo->nb_of_meals >= philo->data->must_eat)
	{
		philo->finish = true;
		return (1);
	}
	return (0);
}

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
	bool	first_time;

	philo = (t_philo *)arg;
	first_time = true;
	pthread_mutex_lock(&philo->data->go_mutex);
	pthread_mutex_unlock(&philo->data->go_mutex);
	wait_till_time(philo->start);
	if (philo->tid % 2 == 0)
		ft_usleep(philo->data, philo->data->t_eat / 4);
	if (philo->data->philo_nb == 1)
			print_status(MSG_FORK, philo);
	else {
		while (!is_dead(philo->data) && !has_eaten_enough(philo))
		{
			if (!first_time && !philo->finish)
			{
				sleeping(philo);
				thinking(philo);
			}
			wait_and_take_forks(philo);
			eating(philo);
			first_time = false;
		}
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
