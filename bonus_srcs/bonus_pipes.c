/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:17:21 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 12:44:47 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

/* Create pipes based on the number of args including here_doc */
void	open_pipes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_n - 1)
	{
		if (pipe(d->pipes + 2 * i) < 0)
			free_parent(d);
		i++;
	}
}

/* Close all pipes */
void	close_pipes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->pipe_n)
	{
		close(d->pipes[i]);
		i++;
	}
}
