/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:17:14 by jgoad             #+#    #+#             */
/*   Updated: 2022/01/13 17:26:09 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

//Define buffer size
# define BUFFER_SIZE 1

int		read_chars(char **store, int fd);
void	get_line(char **store, char **line, int len);
char	*get_next_line(int fd);
int		strlen_char(char *str, char c);
char	*ft_strdup_char(char *s1);
char	*join_free(char *store, char *buffer);

#endif