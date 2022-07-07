/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:04:40 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 18:25:30 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error(char *message)
{
	printf("%s\n", message);
}

void	print_status(int status, long long int start, int tid)
{
	struct timeval	now;
	long long int	now_int;
	long long int	diff;

	gettimeofday(&now, NULL);
	now_int = (now.tv_sec * 1000000) + now.tv_usec;
	diff = now_int - start;
	printf("%lld %d initialized\n", diff, tid);
}
