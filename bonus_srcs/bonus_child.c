/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:38:35 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:14:48 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

/* Build a path for a specific command */
static	char	*build_cmd_path(char **cmd_path, char *cmd)
{
	char	*tmp;
	char	*cmd_res;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[0] == '.' || cmd[i] == '/')
			return (ft_strdup(cmd));
		i++;
	}
	while (*cmd_path)
	{
		tmp = ft_strjoin(*cmd_path, "/");
		cmd_res = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(cmd_res, 0) == 0)
			return (cmd_res);
		free(cmd_res);
		cmd_path++;
	}
	return (NULL);
}

/* Update a single set of pipes */
static	void	update_pipes(int p1, int p2)
{
	dup2(p1, 0);
	dup2(p2, 1);
}

/* Manage pipes for child process */
static	void	manage_pipes(t_data *d)
{
	if (d->c_iter == 0)
		update_pipes(d->fd_src, d->pipes[1]);
	else if (d->c_iter == d->cmd_n - 1)
		update_pipes(d->pipes[2 * d->c_iter - 2], d->fd_dst);
	else
		update_pipes(d->pipes[2 * d->c_iter - 2], d->pipes[2 * d->c_iter + 1]);
	close_pipes(d);
}

/* Run child based on current argument input */
void	run_child(t_data d, char **argv, char **envp)
{
	d.pid_child = fork();
	d.errnum = 0;
	if (!d.pid_child)
	{
		manage_pipes(&d);
		d.cmd_args = ft_split(argv[2 + d.here_doc + d.c_iter], ' ');
		d.cmd = build_cmd_path(d.cmd_path, d.cmd_args[0]);
		if (!d.cmd)
		{
			error_msg_child(d.cmd_args[0], ERR_CMD);
			d.errnum = 127;
		}
		else if (execve(d.cmd, d.cmd_args, envp) == -1)
		{
			error_msg_child(d.cmd, ERR_CMD);
			d.errnum = 127;
		}
		free_child(&d);
		if (d.errnum != 0)
			exit(d.errnum);
	}
}
