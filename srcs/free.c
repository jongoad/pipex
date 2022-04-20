/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:41:23 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:02:16 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* Free parent process resources */
void	free_parent(t_data *d)
{
	int	i;

	i = 0;
	while (d->cmd_path[i])
	{
		free(d->cmd_path[i]);
		i++;
	}
	free(d->cmd_path);
	close(d->fd_src);
	close(d->fd_dst);
}

/* Free child process resources */
void	free_child(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd_args)
	{
		while (d->cmd_args[i])
		{
			free(d->cmd_args[i]);
			i++;
		}
		free(d->cmd_args);
	}
	if (d->cmd)
		free(d->cmd);
}

/* Close both FDs of an open pipe */
void	close_pipe(t_data *d)
{
	close(d->fd_pipe[0]);
	close(d->fd_pipe[1]);
}
