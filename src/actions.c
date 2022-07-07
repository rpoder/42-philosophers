/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:28:18 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 20:41:10 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo, int one, int two)
{
	print_status(MSG_EATING, philo);
	usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->data->chopsticks[one]);
	pthread_mutex_unlock(&philo->data->chopsticks[two]);
}
