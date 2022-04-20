/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:56:22 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:19:27 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
/* Open the correct source file */
void	get_src(t_data *d, char *arg)
{
	d->fd_src = open(arg, O_RDONLY);
	if (d->fd_src < 0)
	{
		perror(arg);
		d->file_valid = 0;
	}
	else
		d->file_valid = 1;
}

/* Open the destination file */
void	get_dst(t_data *d, char *arg)
{
	d->fd_dst = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (d->fd_dst < 0)
		perror(arg);
}

/* Setup to save lines in main function */
static	void	setup(t_data *d, int argc, char *argv[], char *envp[])
{
	get_src(d, argv[1]);
	get_dst(d, argv[argc - 1]);
	if (pipe(d->fd_pipe) < 0)
		error_msg(ERR_PIPE, 1);
	d->path_var = find_path(envp);
	d->cmd_path = ft_split(d->path_var, ':');
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	d;

	if (argc != 5)
		error_msg(ERR_ARGS, 1);
	setup(&d, argc, argv, envp);
	if (d.file_valid)
	{
		d.pid_first = fork();
		if (d.pid_first == 0)
			child_first(d, argv, envp);
	}
	d.pid_last = fork();
	if (d.pid_last == 0)
		child_last(d, argc, argv, envp);
	close_pipe(&d);
	if (d.file_valid)
		waitpid(d.pid_first, &d.status, 0);
	waitpid(d.pid_last, &d.status, 0);
	free_parent(&d);
	if (d.status >> 8 > 0)
		exit(d.status >> 8);
	return (0);
}
