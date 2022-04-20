/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:10:20 by jgoad             #+#    #+#             */
/*   Updated: 2022/04/20 17:15:32 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_pipex.h"

/* Find the PATH variable in envp array */
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/* Print error message and exit */
void	error_msg(char *err, int errnum)
{
	perror(err);
	exit(errnum);
}

/* Print error from child */
void	error_msg_child(char *err, char *arg)
{
	write(2, err, ft_strlen(err));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}
