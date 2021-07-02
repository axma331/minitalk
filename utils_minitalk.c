#include "minitalk.h"

void	last_msg(void)
{
	output_and_exit("\033[32mMsg has been received by server\033[0m", 0);
}

void	output_if_no_sgnl(int pid, int signum)
{
	if (kill(pid, signum) == -1)
		output_and_exit("\033[31mCouldn't send signal!\033[0m", 1);
}

void	flag_changes(void)
{
	g_flag_signal = 1;
}

void	output_pid(pid_t pid)
{
	ft_putendl_fd("\033[32mServer started!\033[0m", STDOUT_FILENO);
	ft_putstr_fd("\033[36mPid: \033[33m", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\033[0m\n", STDOUT_FILENO);
}

void	init_sigaction(int signum, void *action)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(signum, &sa, NULL);
}
