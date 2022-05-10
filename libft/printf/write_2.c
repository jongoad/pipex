/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:37:42 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:35:01 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_uint(unsigned int arg, t_fmt *arg_fmt)
{
	char	*buf;
	int		count;

	buf = itoa_uint(arg);
	if (arg_fmt->is_fmt == 1)
		buf = apply_format(buf, arg_fmt);
	count = putstr_len(buf);
	free(buf);
	return (count);
}

int	write_hex_case(unsigned int arg, int c, t_fmt *arg_fmt)
{
	char	*buf;
	int		count;

	buf = convert_hex_case(arg, c);
	if (arg_fmt->is_fmt == 1)
		buf = apply_format(buf, arg_fmt);
	count = putstr_len(buf);
	free(buf);
	return (count);
}

int	write_percent(char c, t_fmt *arg_fmt)
{
	char	*buf;
	int		count;

	buf = (char *)malloc(2);
	buf[0] = c;
	buf[1] = '\0';
	if (arg_fmt->is_fmt == 1)
		buf = apply_format(buf, arg_fmt);
	count = putstr_len(buf);
	free(buf);
	return (count);
}
