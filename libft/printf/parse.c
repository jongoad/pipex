/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:52:20 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:00:47 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_str(const char *input, int i, char **buf, int *is_arg)
{
	int	start;

	start = i;
	*is_arg = 0;
	if (input[i] != '%')
	{
		while (input[i] && input[i] != '%')
			i++;
		*buf = strdup_len(input, start, i - 1);
	}
	else if (input[i] == '%')
	{
		if (input[i + 1] == '%')
			*is_arg = 2;
		else
			*is_arg = 1;
		i++;
		while (input[i] && !ft_strchr(g_spec, input[i]))
			i++;
		*buf = strdup_len(input, start, i);
		i++;
	}
	return (i);
}

t_fmt	*parse_format(char *format)
{
	t_fmt	*arg_fmt;
	int		i;
	int		j;

	arg_fmt = NULL;
	arg_fmt = init_format_struct(arg_fmt);
	i = 1;
	j = 0;
	if (ft_strchr(g_spec, format[i]))
	{
		arg_fmt->spec = format[i];
		return (arg_fmt);
	}
	else
		arg_fmt->is_fmt = 1;
	arg_fmt = parse_flags(arg_fmt, format, &i, &j);
	arg_fmt = parse_width(arg_fmt, format, &i);
	arg_fmt = parse_precision(arg_fmt, format, &i, &j);
	arg_fmt->spec = format[i];
	return (arg_fmt);
}

t_fmt	*parse_flags(t_fmt *arg_fmt, char *format, int *i, int *j)
{
	int	jj;
	int	ii;

	jj = *j;
	ii = *i;
	while (ft_strchr(g_flag, format[ii]) && format[ii] != '.')
	{
		if (!ft_strchr(arg_fmt->flags, format[ii]))
		{
			arg_fmt->flags[jj] = format[ii];
			jj++;
		}
		ii++;
	}
	*i = ii;
	*j = jj;
	return (arg_fmt);
}

t_fmt	*parse_width(t_fmt *arg_fmt, char *format, int *i)
{
	int	ii;

	ii = *i;
	while ((format[ii] >= '0' && format[ii] <= '9') && format[ii] != '.')
	{
		arg_fmt->width = (arg_fmt->width * 10) + (format[ii] - '0');
		ii++;
	}
	*i = ii;
	return (arg_fmt);
}

t_fmt	*parse_precision(t_fmt *arg_fmt, char *format, int *i, int *j)
{
	int	ii;

	ii = *i;
	if (format[ii] == '.')
	{
		arg_fmt->flags[*j] = '.';
		ii++;
		while (format[ii] >= '0' && format[ii] <= '9')
		{
			arg_fmt->precision = (arg_fmt->precision * 10) + (format[ii] - '0');
			ii++;
		}
	}
	*i = ii;
	return (arg_fmt);
}
