/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:56:22 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:20:12 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

static	void	setup(t_data *d, int argc, char *argv[], char *envp[])
{
	get_src(d, argv);
	get_dst(d, argv[argc - 1]);
	d->cmd_n = argc - 3 - d->here_doc;
	d->pipe_n = 2 * (d->cmd_n - 1);
	d->pipes = (int *)malloc(sizeof(int) * d->pipe_n);
	if (!d->pipes)
		error_msg(ERR_PIPE, 1);
	d->path_var = find_path(envp);
	d->cmd_path = ft_split(d->path_var, ':');
	if (!d->cmd_path)
		free_pipes(d);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	d;

	if (argc < check_args(&d, argv[1]))
		error_msg(ERR_ARGS, 1);
	setup(&d, argc, argv, envp);
	open_pipes(&d);
	d.c_iter = -1;
	while (++d.c_iter < d.cmd_n)
	{
		if ((d.c_iter == 0 && d.file_valid == 1) || d.c_iter > 0)
			run_child(d, argv, envp);
	}
	close_pipes(&d);
	while (wait(&d.status) > 0)
		;
	free_parent(&d);
	if (d.status >> 8 > 0)
		exit(d.status >> 8 > 0);
	return (0);
}
