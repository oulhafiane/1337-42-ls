/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_ops3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:02:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:29:14 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*check_permission(char *path)
{
	DIR		*current;

	if ((current = opendir(path)) == NULL)
		ft_fprintf(2, "ls: %s: Permission denied\n", get_file_name(path));
	return (current);
}

int		check_nonv(char **tab, int count)
{
	int			i;
	int			c_nonv;
	struct stat	st;

	i = -1;
	c_nonv = 0;
	while (++i < count)
	{
		if (lstat(tab[i], &st) != 0)
		{
			ft_fprintf(2, "ls: %s: No such file or directory\n", tab[i]);
			ft_swap_pt((void**)(tab + (c_nonv++)), (void**)(tab + i));
		}
	}
	return (c_nonv);
}

void	set_total(char *name, t_total **total)
{
	struct stat		st;

	if (*total == NULL)
	{
		*total = (t_total*)malloc(sizeof(t_total));
		(*total)->total = 0;
		(*total)->max_uid = 0;
		(*total)->max_gid = 0;
		(*total)->max_link = 0;
		(*total)->max_size = 0;
	}
	if (lstat(name, &st) != 0)
		return ;
	if (((st.st_mode & S_IFMT) == S_IFCHR) || (st.st_mode & S_IFMT) == S_IFBLK)
		(*total)->max_size = 8;
	(*total)->total += st.st_blocks;
	if ((*total)->max_uid < (int)ft_strlen(getpwuid(st.st_uid)->pw_name))
		(*total)->max_uid = (int)ft_strlen(getpwuid(st.st_uid)->pw_name);
	if ((*total)->max_gid < (int)ft_strlen(getgrgid(st.st_gid)->gr_name))
		(*total)->max_gid = (int)ft_strlen(getgrgid(st.st_gid)->gr_name);
	if ((*total)->max_link < ft_nbrlen(st.st_nlink))
		(*total)->max_link = ft_nbrlen(st.st_nlink);
	if ((*total)->max_size < ft_nbrlen(st.st_size))
		(*total)->max_size = ft_nbrlen(st.st_size);
}
