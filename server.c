/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:52:35 by pratanac          #+#    #+#             */
/*   Updated: 2022/04/10 23:58:57 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "minitalk.h"

/* If SIGUSR1 recieve it means 1 but if SIGUSR2 receive it mean 0 */
unsigned char	ft_decoder(int *sequence)
{
	unsigned char	c;
	int				index;

	c = 0;
	index = 0;
	while (index < 8)
	{
		c |= (sequence[index] << (7 - index));
		index++;
	}
	return (c);
}

void	handler_s(int signal, siginfo_t *info, void *uap)
{
	static int		i;
	unsigned char	c;
	static int		sequence[8];

	(void)uap;
	if (signal == SIGUSR1)
		sequence[i++] = 1;
	else if (signal == SIGUSR2)
		sequence[i++] = 0;
	if (i == 8)
	{
		c = ft_decoder(sequence);
		i = 0;
		if (!c)
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		write(1, &c, 1);
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_sigaction = handler_s;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	ft_putstr_fd("Server PID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
