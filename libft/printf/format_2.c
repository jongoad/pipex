/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:39 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:27:17 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero_padding(char *buf, int len)
{
	char	*output;
	int		i;
	int		j;
	int		k;

	j = ft_strlen(buf);
	output = (char *)malloc(len + 1);
	output = (char *)ft_memset((void *)output, '0', len);
	output[len] = '\0';
	i = len - 1;
	k = 0;
	if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X'))
	{	
		output[k++] = buf[0];
		output[k++] = buf[1];
	}
	else if (buf[0] == ' ' || buf[0] == '-' || buf[0] == '+')
		output[k++] = buf[0];
	while (--j >= k)
	{
		output[i] = buf[j];
		i--;
	}
	free(buf);
	return (output);
}

char	*format_signed(char *output, t_fmt *arg_fmt)
{
	char	*buf;
	int		i;

	i = 0;
	if ((ft_strchr(arg_fmt->flags, ' ') || ft_strchr(arg_fmt->flags, '+'))
		&& output[0] != '-' && arg_fmt->spec != 's')
	{
		buf = (char *)malloc(ft_strlen(output) + 2);
		buf[ft_strlen(output) + 1] = '\0';
		if (ft_strchr(arg_fmt->flags, '+'))
			buf[0] = '+';
		else if (ft_strchr(arg_fmt->flags, ' '))
			buf[0] = ' ';
		while (output[i])
		{
			buf[i + 1] = output[i];
			i++;
		}
		free(output);
		output = buf;
	}
	return (output);
}

char	*format_hash(char *output, t_fmt *arg_fmt)
{
	char	*buf;
	int		i;

	i = 0;
	if (ft_strchr(arg_fmt->flags, '#') && output[0] != '0')
	{
		buf = (char *)malloc(ft_strlen(output) + 3);
		buf[ft_strlen(output) + 2] = '\0';
		buf[i++] = '0';
		if (arg_fmt->spec == 'x')
			buf[i++] = 'x';
		else if (arg_fmt->spec == 'X')
			buf[i++] = 'X';
		while (output[i - 2])
		{
			buf[i] = output[i - 2];
			i++;
		}
		free(output);
		return (buf);
	}
	else
		return (output);
}

char	*pad_justify(char *output, t_fmt *arg_fmt)
{
	char	*buf;
	int		i;
	int		j;

	i = -1;
	buf = (char *)malloc(arg_fmt->width + 1);
	buf[arg_fmt->width] = '\0';
	buf = (char *)ft_memset((void *)buf, ' ', arg_fmt->width);
	if (ft_strchr(arg_fmt->flags, '-') && output[0])
	{
		while (output[++i])
			buf[i] = output[i];
	}
	else if (output[0])
	{
		j = ft_strlen(buf) - 1;
		i = ft_strlen(output);
		while (--i >= 0)
		{
			buf[j] = output[i];
			j--;
		}
	}
	free(output);
	return (buf);
}
