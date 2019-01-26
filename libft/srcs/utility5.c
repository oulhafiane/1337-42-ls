/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_pr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:35:42 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/26 21:02:31 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_pr(const char *str)
{
	int i;
	int sign;
	int nbr;
	int c;

	i = 0;
	nbr = 0;
	sign = 0;
	while (str[i] == ' ')
		i++;
	c = i;
	while ((str[i] >= '0' && str[i] <= '9') ||
			(c == i && sign == 0 && (str[i] == '-' || str[i] == '+')))
	{
		if (str[i] == '-' || str[i] == '+')
			sign = str[i];
		else
			nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	if (sign == '-')
		nbr = nbr * -1;
	return (nbr);
}

char	*ft_alloc_mem(char *s, int nb, int flag, int i)
{
	char	*tmp;

	if (s == NULL)
		s = malloc(sizeof(char) * LEN_BUF);
	else if (flag == 1)
	{
		s[i] = '\0';
		tmp = s;
		s = malloc(sizeof(char) * (LEN_BUF) * nb);
		ft_strcpy(s, tmp);
		free(tmp);
	}
	return (s);
}
