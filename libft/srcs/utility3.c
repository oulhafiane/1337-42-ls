/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 21:09:14 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/19 16:03:55 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_max(int len1, int len2)
{
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

int		get_min(int len1, int len2)
{
	if (len1 < len2)
		return (len1);
	else
		return (len2);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*null_str(char str[7])
{
	str[0] = '(';
	str[1] = 'n';
	str[2] = 'u';
	str[3] = 'l';
	str[4] = 'l';
	str[5] = ')';
	str[6] = '\0';
	return (str);
}

char	next_conv(char *s)
{
	int i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (is_conv(s[i], "sSpdDioOuUxXcCeEfFgGaAn%") == 1)
			return (s[i]);
	}
	return (0);
}
