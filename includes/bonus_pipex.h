/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:39:16 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:16:29 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

/* System includes */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

/* User includes */
# include "../libft/libft.h"

/* Error defines */
# define ERR_ARGS "Invalid argument count"
# define ERR_PIPE "Failed to allocate pipes"
# define ERR_INFILE "unable to open infile"
# define ERR_OUTFILE "unable to open/create outfile"
# define ERR_HERE_DOC "here_doc error"
# define ERR_CMD ": command not found"

/* Data struct */
typedef struct s_data
{
	int		fd_src;
	int		fd_dst;
	int		here_doc;
	int		*pipes;
	int		pipe_n;
	char	*path_var;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
	int		cmd_n;
	pid_t	pid_child;
	int		c_iter;
	int		file_valid;
	int		status;
	int		errnum;
}	t_data;

/* Setup functions */
int		check_args(t_data *d, char *arg);
void	read_here_doc(t_data *d, char *arg);
void	get_src(t_data *d, char **argv);
void	get_dst(t_data *d, char *argv);

/* Pipe functions */
void	open_pipes(t_data *d);
void	close_pipes(t_data *d);

/* Main functions */
void	run_child(t_data d, char **argv, char **envp);

/* Free functions */
void	free_parent(t_data *d);
void	free_child(t_data *d);
void	free_pipes(t_data *d);

/* Utility functions */
char	*find_path(char **envp);
void	error_msg(char *err, int errnum);
void	error_msg_child(char *err, char *arg);

#endif