/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:39:12 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:02:05 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_uint(unsigned int n)
{
	int				count;
	char			*str;
	unsigned int	nbr;

	count = count_digits_uint(n);
	nbr = n;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	str[count--] = '\0';
	while (nbr)
	{
		str[count] = (nbr % 10) + '0';
		count--;
		nbr = (nbr / 10);
	}
	return (str);
}

int	count_digits_uint(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count = 1;
	while (nbr)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

char	*ptr_as_hex(size_t ptr)
{
	char	*buf;
	int		i;
	int		j;

	buf = (char *)malloc(19);
	i = 18;
	j = 2;
	while (ptr > 0)
	{
		buf[i] = g_hex_lower[ptr % 16];
		i--;
		ptr = ptr / 16;
	}
	while (++i < 19)
		buf[j++] = buf[i];
	buf[j] = '\0';
	buf[0] = '0';
	buf[1] = 'x';
	return (buf);
}

char	*convert_hex_case(unsigned int n, int c)
{
	char	*buf;
	int		i;
	int		j;

	buf = (char *)malloc(17);
	i = 16;
	j = 0;
	if (n == 0)
	{
		buf[i] = '0';
		i--;
	}
	while (n > 0)
	{
		if (c == 1)
			buf[i] = g_hex_upper[n % 16];
		else
			buf[i] = g_hex_lower[n % 16];
		i--;
		n = n / 16;
	}
	while (++i < 17)
		buf[j++] = buf[i];
	buf[j] = '\0';
	return (buf);
}

t_fmt	*init_format_struct(t_fmt *arg_fmt)
{
	arg_fmt = (t_fmt *)malloc(sizeof(t_fmt));
	arg_fmt->flags = (char *)malloc(7);
	arg_fmt->flags = (char *)ft_memset((void *)arg_fmt->flags, '\0', 7);
	arg_fmt->width = 0;
	arg_fmt->precision = 0;
	arg_fmt->is_fmt = 0;
	return (arg_fmt);
}
