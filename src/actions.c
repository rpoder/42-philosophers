/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:28:18 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/16 19:13:04 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_and_take_forks(t_philo *philo)
{
	if (philo->data->philo_nb == 1)
	{
		pthread_mutex_lock(&philo->data->chopsticks[philo->left]);
		print_status(MSG_FORK, philo);
		return ;
	}
	if (philo->tid % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->chopsticks[philo->left]);
		print_status(MSG_FORK, philo);
		pthread_mutex_lock(&philo->data->chopsticks[philo->right]);
		print_status(MSG_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->data->chopsticks[philo->right]);
		print_status(MSG_FORK, philo);
		pthread_mutex_lock(&philo->data->chopsticks[philo->left]);
		print_status(MSG_FORK, philo);
	}
}

void	eating(t_philo *philo)
{
	struct timeval	now;

	print_status(MSG_EATING, philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(&now, NULL);
	philo->last_meal = (now.tv_sec * 1000000) + now.tv_usec;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->data->chopsticks[philo->left]);
	pthread_mutex_unlock(&philo->data->chopsticks[philo->right]);
}

void	sleeping(t_philo *philo)
{
	print_status(MSG_SLEEPING, philo);
	usleep(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	if (philo->data->t_eat >= philo->data->t_sleep)
	{
		print_status(MSG_THINKING, philo);
		usleep(philo->data->t_eat - philo->data->t_sleep + 1);
	}
}
