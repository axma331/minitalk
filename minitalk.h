#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./libft/libft.h"

int	g_flag_signal;

void	init_sigaction(int signum, void *action);
void	output_pid(pid_t pid);
void	flag_changes(void);
void	output_if_no_sgnl(int pid, int signum);
void	last_msg(void);

void	convers_send(char *argv, char *pid);

void	convertor_input(int signum, siginfo_t *siginfo, void *ucontext);
char	*output_str(char *str, siginfo_t *siginfo);
char	*prepare_str(char *str, char c);

#endif