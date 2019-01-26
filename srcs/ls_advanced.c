/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_advanced.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:10:20 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 14:36:27 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_time(time_t ts)
{
	char	*time_h;
	time_t	current;

	time_h = ft_strdup(ctime(&ts));
	time(&current);
	time_h += 4;
	if (current - ts >= 15690000 || current - ts < 0)
	{
		time_h[7] = ' ';
		time_h[8] = time_h[16];
		time_h[9] = time_h[17];
		time_h[10] = time_h[18];
		time_h[11] = time_h[19];
		time_h[12] = '\0';
	}
	else
		time_h[12] = '\0';
	free(time_h - 4);
	return (time_h);
}

void	print_data(struct stat *st, char *name, t_total *total)
{
	char			*perm;

	perm = translate_mode(st->st_mode);
	if (perm[0] == 'c' || perm[0] == 'b')
		ft_printf("%-11s %*d %-*s%-*s%3d, %3d %s %s", perm,
				total->max_link, st->st_nlink, total->max_uid + 2,
				get_uid(st->st_uid), total->max_gid + 2,
				get_gid(st->st_gid), major(st->st_rdev),
				minor(st->st_rdev), get_time(st->st_mtimespec.tv_sec),
				get_file_name(name));
	else
		ft_printf("%-11s %*d %-*s%-*s%*lld %s %s", perm,
				total->max_link, st->st_nlink, total->max_uid + 2,
				get_uid(st->st_uid), total->max_gid + 2,
				get_gid(st->st_gid), total->max_size, st->st_size,
				get_time(st->st_mtimespec.tv_sec),
				get_file_name(name));
	free(perm);
}

void	ls_print_l(t_list *lst, t_total *total)
{
	struct stat		st;
	char			ln_path[256];

	while (lst)
	{
		if (lstat(lst->content, &st) == 0)
		{
			print_data(&st, get_file_name(lst->content), total);
			if ((st.st_mode & S_IFMT) == S_IFLNK)
			{
				ft_bzero(ln_path, 256);
				if (readlink(lst->content, ln_path, 256) != -1)
					ft_printf(" -> %s", ln_path);
			}
			ft_printf("\n");
		}
		lst = lst->next;
	}
}

void	ls_with_bigr(t_list *lst, char flags[LEN_FL_LS])
{
	DIR				*current;
	struct stat		st;

	while (lst)
	{
		if (ft_strcmp(get_file_name((char*)lst->content), "..") != 0
				&& ft_strcmp(get_file_name((char*)lst->content), ".") != 0
				&& lstat(lst->content, &st) == 0
				&& (st.st_mode & S_IFMT) == S_IFDIR)
		{
			if (((char*)lst->content)[0] == '/' &&
					((char*)lst->content)[1] == '/')
				ft_printf("\n%s:\n", lst->content + 1);
			else
				ft_printf("\n%s:\n", lst->content);
			if ((current = opendir((char*)lst->content)) != NULL)
				ft_ls((char *)lst->content, flags);
			else
				ft_fprintf(2, "ls: %s: Permission denied\n",
						get_file_name((char*)lst->content));
			if (current != NULL)
				closedir(current);
		}
		lst = lst->next;
	}
}
