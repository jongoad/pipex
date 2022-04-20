/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:54:22 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:37:14 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_write(char *format, void *arg)
{
	t_fmt	*arg_fmt;
	int		count;

	count = 0;
	arg_fmt = parse_format(format);
	if (arg_fmt->spec == 'c')
		count = write_char((char)arg, arg_fmt);
	else if (arg_fmt->spec == 's')
		count = write_str((char *)arg, arg_fmt);
	else if (arg_fmt->spec == 'p')
		count = write_ptr((void *)arg, arg_fmt);
	else if (arg_fmt->spec == 'd' || arg_fmt->spec == 'i')
		count = write_int((int)arg, arg_fmt);
	else if (arg_fmt->spec == 'u')
		count = write_uint((unsigned int)arg, arg_fmt);
	else if (arg_fmt->spec == 'x')
		count = write_hex_case((unsigned int)arg, 0, arg_fmt);
	else if (arg_fmt->spec == 'X')
		count = write_hex_case((unsigned int)arg, 1, arg_fmt);
	else if (arg_fmt->spec == '%')
		count = write_percent('%', arg_fmt);
	free(arg_fmt->flags);
	free(arg_fmt);
	return (count);
}

int	write_char(char arg, t_fmt *arg_fmt)
{
	char	*buf;
	int		len;

	if (arg_fmt->is_fmt == 1)
		buf = apply_format_char(arg, arg_fmt, &len);
	else
	{
		buf = (char *)malloc(2);
		buf[0] = arg;
		buf[1] = '\0';
		len = 1;
	}
	putstr_n(buf, len);
	free(buf);
	return (len);
}

int	write_str(char *arg, t_fmt *arg_fmt)
{
	char	*buf;
	int		count;

	if (!arg)
		buf = ft_strdup("(null)");
	else
		buf = ft_strdup(arg);
	if (arg_fmt->is_fmt == 1)
		buf = apply_format(buf, arg_fmt);
	count = putstr_len(buf);
	free(buf);
	return (count);
}

int	write_ptr(void *arg, t_fmt *arg_fmt)
{
	int		count;
	char	*ptr_buf;

	if (!arg)
	{
		ptr_buf = (char *)malloc(4);
		ptr_buf[0] = '0';
		ptr_buf[1] = 'x';
		ptr_buf[2] = '0';
		ptr_buf[3] = '\0';
	}
	else
		ptr_buf = ptr_as_hex((size_t)arg);
	if (arg_fmt->is_fmt == 1)
		ptr_buf = apply_format(ptr_buf, arg_fmt);
	count = putstr_len(ptr_buf);
	free(ptr_buf);
	return (count);
}

int	write_int(int arg, t_fmt *arg_fmt)
{
	char	*buf;
	int		count;

	buf = ft_itoa(arg);
	if (arg_fmt->is_fmt == 1)
		buf = apply_format(buf, arg_fmt);
	count = putstr_len(buf);
	free(buf);
	return (count);
}
