/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:50:59 by pratanac          #+#    #+#             */
/*   Updated: 2022/04/11 00:05:37 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*pointer;
	size_t	count;

	pointer = malloc(num * size);
	count = 0;
	if (!pointer)
		return (NULL);
	while (count < (num * size))
	{
		pointer[count] = '\0';
		count++;
	}
	return ((void *)pointer);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
		return ;
	while (s[count])
	{
		ft_putchar_fd (s[count], fd);
		count++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = (long int)n;
	if (num < 0)
	{
		num = -1 * num;
		ft_putchar_fd('-', fd);
	}
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long int	result;
	int			i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = 10 * result + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}
