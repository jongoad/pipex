/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:56:57 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:03:16 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

/* User includes */
# include "../libft/libft.h"

/* Error defines */
# define ERR_ARGS "Invalid argument count"
# define ERR_CMD ": command not found"
# define ERR_EXEC ": no such file or directory"
# define ERR_PIPE "Failed to open pipe"

typedef struct s_data
{
	int		fd_src;
	int		fd_dst;
	int		file_valid;
	int		fd_pipe[2];
	char	*path_var;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
	pid_t	pid_first;
	pid_t	pid_last;
	int		status;
}	t_data;

/* File functions */
void	get_src(t_data *d, char *arg);
void	get_dst(t_data *d, char *arg);

/* Child functions */
void	child_first(t_data d, char *argv[], char *envp[]);
void	child_last(t_data d, int argc, char *argv[], char *envp[]);

/* Utility functions */
void	close_pipe(t_data *d);
char	*find_path(char **envp);
void	free_parent(t_data *d);
void	free_child(t_data *d);

/* Error functions */
void	error_msg(char *err, int errnum);
void	error_msg_child(char *err, char *arg);

#endif