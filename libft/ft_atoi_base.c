/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:37:35 by jgoad             #+#    #+#             */
/*   Updated: 2022/01/18 15:53:27 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_check(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		else if ((base[i] >= 9 && base[i] <= 13) || base[i] == 32)
			return (0);
		j = 1;
		while (base[i + j] != '\0')
		{
			if (base[i] == base[i + j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	get_base_val(char *str, char *base, int i)
{
	int	j;

	j = 0;
	while (base[j])
	{
		if (base[j] == str[i])
			return (j);
		j++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	i;
	int	n;
	int	base_len;

	n = 0;
	i = -1;
	sign = 1;
	if (base_check(base) == 0)
		return (0);
	base_len = base_check(base);
	if (str[++i] == '-')
		sign = -sign;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i] && get_base_val(str, base, i) != -1)
	{
		n = (n * base_len) + get_base_val(str, base, i);
		i++;
	}
	return (n * sign);
}
