/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:03:48 by jgoad             #+#    #+#             */
/*   Updated: 2022/03/25 13:14:07 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include "../libft.h"

//Format information struct
typedef struct s_fmt
{
	int		width;
	int		precision;
	char	*flags;
	char	spec;
	int		is_fmt;
}				t_fmt;

//Global static strings
static const char	*g_spec = {"cspdiuxX%"};
static const char	*g_flag = {"-0.# +"};
static const char	*g_hex_upper = {"0123456789ABCDEF"};
static const char	*g_hex_lower = {"0123456789abcdef"};

//Main function
int		ft_printf(const char *input, ...);

//Utility functions
int		putchar_len(char c);
int		putstr_len(char *str);
char	*strdup_len(const char *input, int start, int end);
char	*itoa_uint(unsigned int n);
int		count_digits_uint(unsigned int nbr);
void	putstr_n(char *str, int n);

//Input parsing functions
int		get_str(const char *input, int i, char **buf, int *is_arg);
char	find_type(char *str);

//Conversion functions
char	*ptr_as_hex(size_t ptr);
char	*convert_hex_case(unsigned int n, int c);

//Writing functions
int		format_write(char *format, void *arg);
int		write_char(char arg, t_fmt *arg_fmt);
int		write_str(char *arg, t_fmt *arg_fmt);
int		write_ptr(void *arg, t_fmt *arg_fmt);
int		write_int(int arg, t_fmt *arg_fmt);
int		write_uint(unsigned int arg, t_fmt *arg_fmt);
int		write_hex_case(unsigned int arg, int c, t_fmt *arg_fmt);
int		write_percent(char c, t_fmt *arg_fmt);

//Bonus Functions

//Format parsing functions
t_fmt	*parse_format(char *format);
t_fmt	*init_format_struct(t_fmt *arg_fmt);
t_fmt	*parse_flags(t_fmt *arg_fmt, char *format, int *i, int *j);
t_fmt	*parse_width(t_fmt *arg_fmt, char *format, int *i);
t_fmt	*parse_precision(t_fmt *arg_fmt, char *format, int *i, int *j);

//Formatting functions
char	*apply_format(char *buf, t_fmt *arg_fmt);
char	*apply_format_char(char arg, t_fmt *arg_fmt, int *len);
char	*format_signed(char *output, t_fmt *arg_fmt);
char	*format_hash(char *output, t_fmt *arg_fmt);
char	*pad_justify(char *output, t_fmt *arg_fmt);
char	*apply_prepend(char *buf, t_fmt *arg_fmt);
char	*apply_precision_str(char *buf, t_fmt *arg_fmt);
char	*apply_precision(char *buf, t_fmt *arg_fmt);
char	*zero_padding(char *buf, int len);

#endif