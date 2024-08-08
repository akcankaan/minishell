#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void debug_tokens(t_data *data) {
    t_token *token = data->token;
    while (token) {
        printf("Token value: %s\n", token->value);
        token = token->next;
    }
}
void rdir_dup(int fd, int new_fd)
{
    if ((fd == new_fd) && fd == -1)
    {
        ft_putstr_fd(" No such file or directory\n", 2);
        close(fd);
        exit(1);
    }
    dup2(fd, new_fd);
    close(fd);
}

void hande_redirection(t_token *node)
{
    while (node && (rdir(node) || is_args(node)))
    {
        if(node->type == REDIRECT_IN)
            rdir_dup(open(node->next->value, O_RDONLY), STDIN_FILENO);
        else if(node->type == REDIRECT_OUT)
            rdir_dup(open(node->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644), STDOUT_FILENO);
        else if(node->type == APPEND)
            rdir_dup(open(node->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644), STDOUT_FILENO);
        node = node->next;
    }
}
void single_command(t_data *data) {
    while (data->token) {
        if (is_args(data->token)) {
            if (!ft_strcmp(data->token->value, "echo"))
                echo(data);
            else if (!ft_strcmp(data->token->value, "env"))
                env(data);
            else if (!ft_strcmp(data->token->value, "pwd"))
                cmd_pwd();
            else if (!ft_strcmp(data->token->value, "exit"))
                cmd_exit(data); // burası multi commandlar düzenlendiğinde parser içerisi düzenlenecek ve çalıştırılacak.
            else if (!ft_strcmp(data->token->value, "export"))
                cmd_export(data);
            else if (!ft_strcmp(data->token->value, "unset"))
                cmd_unset(data);
            else if (!ft_strcmp(data->token->value, "cd")) {
                cmd_cd(data, data->token->next);
                data->token = data->token->next; // 'cd' komutunun argümanını atla
            }
            else
                use_execve(data);
        }
        if (data->token)
            data->token = data->token->next;
    }
}
void	pars_multiple(t_data *data, int pipes, int heredoc, int in_fd)
{
	t_token	*node;
	pid_t	pid;
	int		pipfd[2];
	char	**env;
	char	*path;
	char	**args;
	int		in;
	int		out;

	in = 0;
	out = 0;
	env = env_to_char(data);
	node = data->token;
	while (node)
	{
		if (is_args(node) || heredoc || rdir(node))
		{
			if (is_args(node))
			{
				path = finding_path(data, node);
				args = get_command_args(node);
			}
			while (node && is_args(node))
				node = node->next;
			if (pipes)
				if (pipe(pipfd) == -1)
					ft_exit();
			pid = fork();
			if (pid == -1)
				ft_exit();
			if (pid == 0)
			{
				if (node && rdir(node))
					hande_redirection(node);
				while (node && node->type != PIPE)
				{
					if (node->type == APPEND || node->type == REDIRECT_OUT)
						out = 1;
					else if (node->type == REDIRECT_IN || node->type == HERADOC)
						in = 1;
					node = node->next;
				}
				if (in_fd != 0)
				{
					if (!in)
					{
						dup2(in_fd, 0);
						close(in_fd);
					}
					else
						close(pipfd[0]);
				}
				if (node && node->type == PIPE)
				{
					if (!out)
						dup2(pipfd[1], 1);
					close(pipfd[1]);
				}
				close(pipfd[0]);
				out = 0;
				in = 0;
				if (execve(path, args, env) == -1)
					perror("execve");
				ft_exit();
			}
			else
			{
				if (in_fd != 0)
					close(in_fd);
				if (heredoc)
				{
					waitpid(pid, get_exit_status(), 0);
					heredoc = 0;
				}
				while (node && node->type != PIPE)
					node = node->next;
				if (!(node && node->type == PIPE))
				{
					pipes = 0;
					waitpid(pid, get_exit_status(), 0);
				}
				if (node && node->type == PIPE)
				{
					close(pipfd[1]);
					in_fd = pipfd[0];
				}
				else if (--pipes)
				{
					close(pipfd[0]);
					close(pipfd[1]);
				}
				update_exit_status(data);
			}
		}
		if (node)
			node = node->next;
	}
	while (wait(NULL) > 0)
		;
}

void	multiple_cmd(t_data *data)
{
	t_token	*node;
	int		in_fd;
	int		pipe;
	int		heradoc;

	in_fd = 0;
	pipe = 0;
	heradoc = 0;
	node = data->token;
	while (node)
	{
		if (rdir(node) == 2)
			heradoc = 1;
		if (node->type == PIPE)
			pipe++;
		node = node->next;
	}
	pars_multiple(data, pipe, heradoc, in_fd);
}
int how_many_command(t_data *data)
{
    t_token *node;

    node = data->token;
    if((is_args(node) && !node->next))
        return(1);
    else
    {
        while (node)
        {
            if (node->type == PIPE || rdir(node))
                return (0);
            node = node->next;
        }
        return (1);
    }
    return (0);
}

void parse_commands(t_data *data)
{
    if (!data->token)
        return;

    if (how_many_command(data) == 1)
        single_command(data);
    else
        multiple_cmd(data);
}
