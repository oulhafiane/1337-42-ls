/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:22:37 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:16:34 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				is_flag_good(char flag, char *list_flags)
{
	while (*list_flags != '\0')
	{
		if (flag == *list_flags)
			return (1);
		list_flags++;
	}
	return (0);
}

static int		set_flags(char flags[LEN_FL_LS], char *flag, int count)
{
	flag++;
	while (*flag != '\0')
	{
		if (*flag == 'l' && ft_strchr(flags, '1') != NULL)
			ft_strchr(flags, '1')[0] = *flag;
		else if (*flag == '1' && ft_strchr(flags, 'l') != NULL)
			ft_strchr(flags, 'l')[0] = *flag;
		else if (is_flag_good(*flag, flags) == 0 &&
				is_flag_good(*flag, "1lrRat"))
			flags[count++] = *flag;
		else if (is_flag_good(*flag,
					"ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1") == 0)
		{
			ft_fprintf(2, "ls: illegal option -- %c\n", *flag);
			ft_fprintf(2, "usage: ls ");
			ft_fprintf(2,
					"[-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			return (-1);
		}
		flag++;
	}
	return (count);
}

int				get_flags_ls(int argc, char **argv, char flags[LEN_FL_LS])
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < LEN_FL_LS)
		flags[i] = 0;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
			return (i + 1);
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if ((count = set_flags(flags, argv[i], count)) == -1)
				return (-1);
		}
		else
			return (i);
	}
	return (0);
}
