/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:42:56 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/17 21:26:11 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

static int	check_values(char **args)
{
	if (ft_atol(args[0]) <= 0)
	{
		print_error("Un philosophe est necessaire.");
		return (0);
	}
	if (ft_atol(args[1]) <= 0)
	{
		print_error("Time to die doit etre superieur a 0.");
		return (0);
	}
	if (ft_atol(args[2]) <= 0)
	{
		print_error("Time to eat doit etre superieur a 0");
		return (0);
	}
	if (ft_atol(args[3]) <= 0)
	{
		print_error("Time to sleep doit etre superieur a 0");
		return (0);
	}
	if (args[4] && ft_atol(args[4]) <= 0)
		return (0);
	return (1);
}

static int	check_numbers(char **args)
{
	if (!str_isdigit(args[0]) || !str_isdigit(args[1])
		|| !str_isdigit(args[2]) || !str_isdigit(args[3]))
	{
		print_error("Numbers are not digits.");
		return (0);
	}
	if (args[4] && !str_isdigit(args[4]))
	{
		print_error("Numbers are not digits.");
		return (0);
	}
	if (!ft_is_int(ft_atol(args[0])) || !ft_is_int(ft_atol(args[1]))
		|| !ft_is_int(ft_atol(args[2])) || !ft_is_int(ft_atol(args[3])))
	{
		print_error("Numbers are not integers or positive integers.");
		return (0);
	}
	if (args[4] && !ft_is_int(ft_atol(args[4])))
	{
		print_error("Numbers are not integers or positive integers.");
		return (0);
	}
	if (!check_values(args))
		return (0);
	return (1);
}

t_data	*parse(int argc, char **argv)
{
	char	**args;
	t_data	*data;

	args = argv + 1;
	if (argc != 5 && argc != 6)
	{
		print_error("Wrong number of arguments.");
		return (NULL);
	}
	if (args[0] && args[1] && args[2] && args[3])
		if (!check_numbers(args))
			return (0);
	data = init_data(args);
	if (!data)
		return (NULL);
	return (data);
}
