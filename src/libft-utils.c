/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:55:07 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/16 19:05:54 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

size_t	ft_putnbr_fd(long long int n, int fd)
{
	unsigned int	nb;
	size_t			value;

	value = 0;
	if (n < 0)
	{
		value += ft_putchar_fd('-', fd);
		nb = -n;
	}
	else
		nb = n;
	if (nb > 9)
	{
		value += ft_putnbr_fd(nb / 10, fd);
		nb = nb % 10;
	}
	value += ft_putchar_fd(nb + '0', fd);
	return (value);
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_putstr_fd(char *s, int fd)
{
	int		s_len;
	size_t	value;

	value = 0;
	if (s)
	{
		s_len = ft_strlen(s);
		value += write(fd, s, s_len);
	}
	return (value);
}

long int	ft_atol(char *s)
{
	long int		res;
	int				neg;
	int				i;

	res = 0;
	neg = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + ((long int) s[i] - 48);
		i++;
	}
	return ((long int)res * neg);
}

int	ft_atoi(const char *s)
{
	unsigned long	res;
	int				neg;
	int				i;

	res = 0;
	neg = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + ((unsigned long) s[i] - 48);
		i++;
	}
	if (res > 2147483647 && neg == 1)
		return (-1);
	if (res > 2147483648 && neg == -1)
		return (0);
	return ((int)(res * neg));
}

int	ft_is_int(long int num)
{
	if (!ft_is_positive(num))
		return (0);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (1);
}

int	ft_is_positive(long int num)
{
	if (num < 0)
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
