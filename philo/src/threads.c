/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/18 12:55:56 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	has_eaten_enough(t_philo *philo)
{
	if (philo->data->must_eat == -1)
		return (0);
	if (philo->nb_of_meals > philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->finish_mutex);
		philo->finish = true;
		pthread_mutex_unlock(&philo->finish_mutex);
		return (1);
	}
	return (0);
}

static void	pre_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->go_mutex);
	pthread_mutex_unlock(&philo->data->go_mutex);
	wait_till_time(philo->start);
	if (philo->tid % 2 == 0)
		ft_usleep(philo->data, philo->data->t_eat / 4);
}

void static	sleep_and_think(t_philo *philo)
{
	pthread_mutex_unlock(&philo->finish_mutex);
	sleeping(philo);
	thinking(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	first_time;

	philo = (t_philo *)arg;
	first_time = true;
	pre_routine(philo);
	if (philo->data->philo_nb == 1)
		print_status(MSG_FORK, philo);
	else
	{
		while (!is_dead(philo->data) && !has_eaten_enough(philo))
		{
			pthread_mutex_lock(&philo->finish_mutex);
			if (!first_time && !philo->finish)
				sleep_and_think(philo);
			else
				pthread_mutex_unlock(&philo->finish_mutex);
			wait_and_take_forks(philo);
			eating(philo);
			first_time = false;
		}
	}
	return (NULL);
}
