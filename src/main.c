/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:42 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 17:54:07 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse(argc, argv);
	if (!data)
		return (-1);
	lauch_threads(data);
	join_threads(data);
	free_all(data);
	return (0);
}
