/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:17:19 by pratanac          #+#    #+#             */
/*   Updated: 2022/04/11 00:11:57 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

int	*ft_encoder(unsigned char c)
{
	int	*sequence;
	int	index;

	index = 7;
	sequence = ft_calloc(sizeof(int), 8);
	if (!sequence)
		return (NULL);
	while (index >= 0)
	{
		if (c >= 2)
		{
			sequence[index] = c % 2;
			c = c / 2;
		}
		else
		{
			sequence[index] = c;
			c = c / 2;
		}
		index--;
	}
	return (sequence);
}

void	send_info(pid_t pid, int *sequence)
{
	int	index;

	index = 0;
	if (pid <= 0 || kill(pid, 0) < 0)
	{
		ft_putstr_fd("Invalid PID...\n", 1);
		free(sequence);
		exit(0);
	}
	while (index <= 7)
	{
		if (sequence[index] == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep (50);
		index++;
	}
	free(sequence);
}

static void	handler_c(int signal)
{
	static int	receive = 0;

	if (signal == SIGUSR1)
		receive++;
	else
	{
		ft_putstr_fd("We already send... ", 1);
		ft_putnbr_fd(receive, 1);
		ft_putstr_fd(" bytes\n", 1);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	int			index;
	int			*sequence;

	index = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Error with argument number...\n", 1);
		return (0);
	}
	signal(SIGUSR1, handler_c);
	signal(SIGUSR2, handler_c);
	pid = ft_atoi(argv[1]);
	while (argv[2][index])
	{
		sequence = ft_encoder(argv[2][index]);
		send_info(pid, sequence);
		index++;
	}
	sequence = ft_encoder(0);
	send_info(pid, sequence);
	while (1)
		pause();
	return (0);
}
