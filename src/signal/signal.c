/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:29:55 by mehakcan          #+#    #+#             */
/*   Updated: 2024/09/10 12:53:59 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

int	*get_sig_stat(void)
{
	static int	sig_stat = 0;

	return (&sig_stat);
}

void	handle_sigint(int sig)
{
	*get_exit_status() = 128 + sig;
	if (*get_sig_stat() == HERE_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_exit(NULL);
	}
	else if (*get_sig_stat() == EXEC_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (*get_sig_stat() == PROMT_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	*get_exit_status() = 128 + sig;
	printf("Quit : %d\n", sig);
	rl_replace_line("", 0);
}

void	signal_base(void)
{
	if (*get_sig_stat() == EXEC_SIG)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
