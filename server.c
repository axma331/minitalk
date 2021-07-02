#include "minitalk.h"

char	*output_str(char *str, siginfo_t *siginfo)
{
	ft_putendl_fd(str, 1);
	if (str)
		free(str);
	str = NULL;
	output_if_no_sgnl(siginfo->si_pid, SIGUSR1);
	return (str);
}

char	*prepare_str(char *str, char c)
{
	char	*c_str;
	char	*str_tmp;

	c_str = (char *)malloc(sizeof(char) * 2);
	ft_bzero(c_str, sizeof(char) * 2);
	*c_str = c;
	str_tmp = str;
	str = ft_strjoin(str, c_str);
	usleep(20);
	if (str_tmp)
		free(str_tmp);
	free(c_str);
	c_str = NULL;
	return (str);
}

void	convertor_input(int signum, siginfo_t *siginfo, void *ucontext)
{
	static int	mask;
	static char	c;
	static char	*str;

	(void)ucontext;
	if (!str)
	{
		c = 0;
		mask = 0b10000000;
		str = (char *)malloc(sizeof(char));
		ft_bzero(str, sizeof(char));
	}
	if (signum == SIGUSR1)
		c += mask;
	mask >>= 1;
	if (mask == 0)
	{
		if (c == '\0')
			str = output_str(str, siginfo);
		else
			str = prepare_str(str, c);
		mask = 0b10000000;
		c = 0;
	}
	output_if_no_sgnl (siginfo->si_pid, SIGUSR2);
}

int	main(void)
{
	output_pid(getpid());
	init_sigaction(SIGUSR1, convertor_input);
	init_sigaction(SIGUSR2, convertor_input);
	while (1)
		continue ;
	return (0);
}
