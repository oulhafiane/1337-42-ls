/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:04:39 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/26 21:08:11 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		g_output_fd;

int		print_format(int flags[LEN], va_list ap)
{
	convert_flags(flags);
	if (flags[0] == 's' || flags[0] == 'c')
	{
		if (putstr_flag(flags, ap) == -1)
			return (-1);
	}
	else if (flags[0] == 'd' || flags[0] == 'i')
		putnbr_flag(flags, ap);
	else if (flags[0] == 'u')
		putnbr_u_flag(flags, ap);
	else if (flags[0] == 'p' || flags[0] == 'x' || flags[0] == 'X' ||
			flags[0] == 'o')
		putnbrbase_flag(flags, ap);
	else
		putstr_pr((char*)&flags[0], flags);
	return (0);
}

int		print_stack(char *s, int *i, int *len, int nb)
{
	int tmp;

	if (*i + 1 < LEN_BUF * nb)
		s[++(*i)] = '\0';
	tmp = ft_strlen(s);
	write(g_output_fd, s, tmp);
	*i = -1;
	while (++(*i) < LEN_BUF * nb)
		s[*i] = '\0';
	*i = -1;
	tmp += *len;
	*len = 0;
	return (tmp);
}

int		stock_char(char c, int print)
{
	static char	*s;
	static int	i = -1;
	static int	nb = 1;
	static int	len = 0;

	s = ft_alloc_mem(s, nb, 0, 0);
	if (print == 1)
		return (print_stack(s, &i, &len, nb));
	if (c == '\0')
	{
		len = ft_strlen(s);
		write(g_output_fd, s, len);
		write(g_output_fd, &c, 1);
		i = -1;
		while (++i < LEN_BUF * nb)
			s[i] = '\0';
		i = -1;
		len++;
		return (0);
	}
	if (i + 2 >= LEN_BUF * nb)
		s = ft_alloc_mem(s, ++nb, 1, i + 1);
	s[++i] = c;
	return (0);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			count;
	int			flags[LEN];

	g_output_fd = fd;
	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && format[1] != '\0')
		{
			get_flags((char**)&format, ap, flags);
			if (print_format(flags, ap) != -1)
				count += stock_char('\0', 1);
			else
				return (-1);
		}
		else if (*format != '%')
			stock_char(*format, 0);
		if (*format != '\0')
			format++;
	}
	count += stock_char('\0', 1);
	va_end(ap);
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			count;
	int			flags[LEN];

	g_output_fd = 1;
	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && format[1] != '\0')
		{
			get_flags((char**)&format, ap, flags);
			if (print_format(flags, ap) != -1)
				count += stock_char('\0', 1);
			else
				return (-1);
		}
		else if (*format != '%')
			stock_char(*format, 0);
		if (*format != '\0')
			format++;
	}
	count += stock_char('\0', 1);
	va_end(ap);
	return (count);
}
