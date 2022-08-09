/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:28:18 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/09 17:10:03 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_and_take_forks(t_philo *philo)
{
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
	print_status(MSG_EATING, philo);
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
	if (philo->data->t_eat > philo->data->t_sleep)
	{
		print_status(MSG_THINKING, philo);
		usleep(philo->data->t_eat - philo->data->t_sleep + 1);
	}
}
