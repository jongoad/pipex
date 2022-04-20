/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:52:09 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 14:53:54 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *input, ...)
{
	char	*buffer;
	int		count;
	int		i;
	int		is_arg;
	va_list	args;

	count = 0;
	i = 0;
	va_start(args, input);
	while (input[i])
	{
		i = get_str(input, i, &buffer, &is_arg);
		if (is_arg == 1)
			count += format_write(buffer, va_arg(args, void *));
		else if (is_arg == 2)
			count += format_write(buffer, NULL);
		else
			count += putstr_len(buffer);
		if (*buffer)
			free(buffer);
	}
	va_end(args);
	return (count);
}
