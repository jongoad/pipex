/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:17:21 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:19:57 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

/* Free parent */
void	free_parent(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd_path)
	{
		while (d->cmd_path[i])
		{
			free(d->cmd_path[i]);
			i++;
		}
		free(d->cmd_path);
	}
	if (d->here_doc)
		unlink(".tmp");
	close(d->fd_src);
	close(d->fd_dst);
	if (d->pipes)
		free(d->pipes);
}

/* Free a child */
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

/* Free and exit incse of cmd path error */
void	free_pipes(t_data *d)
{
	close(d->fd_src);
	close(d->fd_src);
	if (d->here_doc)
		unlink(".tmp");
	if (d->pipes)
		free(d->pipes);
	error_msg("invalid command path", 127);
}
