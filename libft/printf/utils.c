/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:04:45 by jgoad             #+#    #+#             */
/*   Updated: 2021/11/12 15:03:37 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_len(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr_len(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count += putchar_len(*str);
		str++;
	}
	return (count);
}

void	putstr_n(char *str, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		count += putchar_len(str[i]);
		i++;
	}
}

char	*strdup_len(const char *input, int start, int end)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(end - start + 2);
	if (!str)
		return (NULL);
	while (input[start] && start <= end)
	{
		str[i] = input[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	find_type(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(g_spec, str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}
