#include "minitalk.h"

void	convers_send(char *argv, char *pid)
{
	int	mask;

	mask = 0b10000000;
	while (mask)
	{
		usleep(50);
		if (*argv & mask)
			output_if_no_sgnl(ft_atoi(pid), SIGUSR1);
		else
			output_if_no_sgnl(ft_atoi(pid), SIGUSR2);
		mask >>= 1;
		while (1)
		{
			if (g_flag_signal == 1)
			{
				g_flag_signal = 0;
				break ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	g_flag_signal = 0;
	if (argc != 3)
		output_and_exit("\033[31mInvalid count of arguments! \
		 \033[33mUsage: ./client <PID> some_msg\033[0m", 1);
	init_sigaction(SIGUSR1, last_msg);
	init_sigaction(SIGUSR2, flag_changes);
	while (1)
	{
		convers_send(&argv[2][i], argv[1]);
		if (argv[2][i++] == '\0')
			break ;
	}
	while (1)
		continue ;
	return (0);
}
