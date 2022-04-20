/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:26:07 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:51:22 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_format(char *buf, t_fmt *arg_fmt)
{
	if (ft_strchr(arg_fmt->flags, '.') && arg_fmt->spec == 's')
		buf = apply_precision_str(buf, arg_fmt);
	buf = apply_prepend(buf, arg_fmt);
	if ((arg_fmt->spec == 'd' || arg_fmt->spec == 'i'
			|| arg_fmt->spec == 'u' || arg_fmt->spec == 'x'
			|| arg_fmt->spec == 'X') && ft_strchr(arg_fmt->flags, '.'))
		buf = apply_precision(buf, arg_fmt);
	if ((ft_strlen(buf) < (size_t)arg_fmt->width)
		&& ft_strchr(arg_fmt->flags, '0')
		&& !ft_strchr(arg_fmt->flags, '.')
		&& !ft_strchr(arg_fmt->flags, '-'))
		buf = zero_padding(buf, arg_fmt->width);
	else if (ft_strlen(buf) < (size_t)arg_fmt->width)
		buf = pad_justify(buf, arg_fmt);
	return (buf);
}

char	*apply_format_char(char arg, t_fmt *arg_fmt, int *len)
{
	char	*buf;

	if (arg_fmt->width > 1)
	{
		buf = (char *)malloc(arg_fmt->width + 1);
		buf = (char *)ft_memset((void *)buf, ' ', arg_fmt->width);
		buf[arg_fmt->width] = '\0';
		if (ft_strchr(arg_fmt->flags, '-'))
			buf[0] = arg;
		else
			buf[arg_fmt->width - 1] = arg;
		*len = arg_fmt->width;
		return (buf);
	}
	else
	{
		buf = (char *)malloc(2);
		buf[0] = arg;
		buf[1] = '\0';
		*len = 1;
		return (buf);
	}
}

char	*apply_prepend(char *buf, t_fmt *arg_fmt)
{
	char	*output;

	if (ft_strchr(arg_fmt->flags, '#'))
		output = format_hash(buf, arg_fmt);
	else if (ft_strchr(arg_fmt->flags, ' ') || ft_strchr(arg_fmt->flags, '+'))
		output = format_signed(buf, arg_fmt);
	else
	{
		output = ft_strdup(buf);
		free(buf);
	}
	return (output);
}

char	*apply_precision_str(char *buf, t_fmt *arg_fmt)
{
	char	*output;

	if (arg_fmt->precision == 0 && arg_fmt->spec == 's')
	{
		output = (char *)malloc(1);
		output[0] = '\0';
	}
	else if (ft_strlen(buf) > (size_t)arg_fmt->precision)
		output = strdup_len(buf, 0, arg_fmt->precision - 1);
	else
		output = ft_strdup(buf);
	free(buf);
	return (output);
}

char	*apply_precision(char *buf, t_fmt *arg_fmt)
{
	char	*output;
	int		j;
	int		k;

	k = 0;
	if (buf[0] == '0' && buf[1] == '\0' && arg_fmt->precision == 0)
		buf[0] = '\0';
	else if (buf[0] == ' ' || buf[0] == '+' || buf[0] == '-')
		k = 1;
	else if (buf[0] == '0' && (buf[1] == 'X' || buf[1] == 'x'))
		k = 2;
	j = ft_strlen(buf) - k;
	if (j >= arg_fmt->precision)
		return (buf);
	else
		output = zero_padding(buf, arg_fmt->precision + k);
	return (output);
}
