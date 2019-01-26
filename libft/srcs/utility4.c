/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:53:26 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/24 23:04:00 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_null(char *s, int cpt_null)
{
	int i;
	int cpt;

	cpt = -1;
	i = -1;
	while (++cpt < cpt_null)
	{
		while (s[++i] != '\0')
			;
	}
	return (i - 1);
}

wchar_t	*null_str_w(wchar_t str[7], int flags[LEN])
{
	if (flags[9] == 1 && flags[6] <= 0)
		return (L"");
	str[0] = '(';
	str[1] = 'n';
	str[2] = 'u';
	str[3] = 'l';
	str[4] = 'l';
	str[5] = ')';
	str[6] = '\0';
	return (str);
}

void	init_s(char s[5])
{
	int i;

	i = -1;
	while (++i < 5)
		s[i] = '\0';
}

void	convert_flags(int flags[LEN])
{
	if (flags[0] == 'D' || flags[0] == 'O' || flags[0] == 'U'
			|| flags[0] == 'C' || flags[0] == 'S')
	{
		flags[0] += 32;
		flags[8] = 'l';
	}
}
