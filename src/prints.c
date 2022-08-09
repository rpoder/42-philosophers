/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:04:40 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/09 14:33:03 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error(char *message)
{
	printf("%s\n", message);
}

void	print_status(int status, t_philo *philo)
{
	struct timeval	now;
	long long int	now_int;
	long long int	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	gettimeofday(&now, NULL);
	now_int = (now.tv_sec * 1000000) + now.tv_usec;
	timestamp = (now_int - philo->start) / 1000;
	if (status == MSG_FORK)
		printf("%lld %d has taken a fork\n", timestamp, philo->tid);
	if (status == MSG_EATING)
		printf("%lld %d is eating\n", timestamp, philo->tid);
	if (status == MSG_SLEEPING)
		printf("%lld %d is sleeping\n", timestamp, philo->tid);
	if (status == MSG_THINKING)
		printf("%lld %d is thinking\n", timestamp, philo->tid);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
