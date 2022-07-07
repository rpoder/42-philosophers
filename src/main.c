/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:42 by rpoder            #+#    #+#             */
/*   Updated: 2022/07/07 18:05:33 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data			*data;

	data = parse(argc, argv);
	if (!data)
		return (0);
	lauch_threads(data);
	join_threads(data);
	//free_all(data);
	return (1);
}
