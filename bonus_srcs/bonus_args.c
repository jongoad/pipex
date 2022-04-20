/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:38:10 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:13:57 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

/* Check for presence of here_doc and return number of args */
int	check_args(t_data *d, char *arg)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		d->here_doc = 1;
		return (6);
	}
	else
	{
		d->here_doc = 0;
		return (5);
	}
}

/* Write to tmp here_doc file */
static	void	write_here_doc(int fd, char **buffer)
{
	write(fd, *buffer, ft_strlen(*buffer));
	write(fd, "\n", 1);
}

/* Create temp file to write here_doc args to */
void	read_here_doc(t_data *d, char *arg)
{
	int		fd;
	char	*b;

	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		error_msg(ERR_HERE_DOC, 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		b = get_next_line(0);
		if (!b)
			exit(1);
		if (!ft_strncmp(arg, b, ft_strlen(arg)) && b[ft_strlen(arg) + 1] == 0)
			break ;
		write_here_doc(fd, &b);
		free(b);
	}
	free(b);
	close(fd);
	d->fd_src = open(".tmp", O_RDONLY);
	if (d->fd_src < 0)
	{
		unlink(".tmp");
		error_msg(ERR_HERE_DOC, 1);
	}
}

/* Open the correct source file */
void	get_src(t_data *d, char **argv)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		read_here_doc(d, argv[2]);
		d->file_valid = 1;
	}
	else
	{
		d->fd_src = open(argv[1], O_RDONLY);
		if (d->fd_src < 0)
		{
			perror(argv[1]);
			d->file_valid = 0;
		}
		else
			d->file_valid = 1;
	}
}

/* Open the destination file */
void	get_dst(t_data *d, char *argv)
{
	if (d->here_doc)
		d->fd_dst = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		d->fd_dst = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (d->fd_dst < 0)
		error_msg(ERR_OUTFILE, 127);
}
