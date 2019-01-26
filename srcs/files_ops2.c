/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:15:57 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:02:32 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_bytime(char *file1, char *file2)
{
	struct stat		st1;
	struct stat		st2;
	int				diff;

	if (lstat(file1, &st1) == 0 && lstat(file2, &st2) == 0)
	{
		diff = st2.st_mtimespec.tv_sec - st1.st_mtimespec.tv_sec;
		if (diff == 0)
			return (ft_strcmp(file1, file2));
		return (diff);
	}
	return (0);
}

int		cmp_files_bytime(t_list *first, t_list *second)
{
	return (cmp_bytime(first->content, second->content));
}

int		cmp_files(t_list *first, t_list *second)
{
	return (ft_strcmp(first->content, second->content));
}

void	print_one_file(void *name)
{
	ft_putendl(get_file_name((char*)name));
}

void	free_lst(void *content, size_t size)
{
	ft_bzero(content, size);
	free(content);
}
