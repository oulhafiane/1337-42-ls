/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:03:35 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:29:15 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_perm_oth(mode_t mode, char *perm)
{
	if ((mode & S_IROTH) == 0)
		perm[7] = '-';
	if ((mode & S_IWOTH) == 0)
		perm[8] = '-';
	if ((mode & S_IXOTH) == 0 && ((mode & S_ISVTX) != 0))
		perm[9] = 'T';
	else if ((mode & S_ISVTX) != 0)
		perm[9] = 't';
	else if ((mode & S_IXOTH) == 0)
		perm[9] = '-';
}

void	set_perm(mode_t mode, char *perm)
{
	if ((mode & S_IRUSR) == 0)
		perm[1] = '-';
	if ((mode & S_IWUSR) == 0)
		perm[2] = '-';
	if ((mode & S_IXUSR) == 0 && (mode & S_ISUID) != 0)
		perm[3] = 'S';
	else if ((mode & S_ISUID) != 0)
		perm[3] = 's';
	else if ((mode & S_IXUSR) == 0)
		perm[3] = '-';
	if ((mode & S_IRGRP) == 0)
		perm[4] = '-';
	if ((mode & S_IWGRP) == 0)
		perm[5] = '-';
	if ((mode & S_IXGRP) == 0 && (mode & S_ISGID) != 0)
		perm[6] = 'S';
	else if ((mode & S_ISGID) != 0)
		perm[6] = 's';
	else if ((mode & S_IXGRP) == 0)
		perm[6] = '-';
	set_perm_oth(mode, perm);
}

char	*translate_mode(mode_t mode)
{
	char	*perm;

	perm = (char*)malloc(sizeof(char) * 12);
	if ((mode & S_IFMT) == S_IFDIR)
		perm[0] = 'd';
	else if ((mode & S_IFMT) == S_IFREG)
		perm[0] = '-';
	else if ((mode & S_IFMT) == S_IFLNK)
		perm[0] = 'l';
	else if ((mode & S_IFMT) == S_IFBLK)
		perm[0] = 'b';
	else if ((mode & S_IFMT) == S_IFCHR)
		perm[0] = 'c';
	else if ((mode & S_IFMT) == S_IFSOCK)
		perm[0] = 's';
	else if ((mode & S_IFMT) == S_IFIFO)
		perm[0] = 'p';
	ft_strcpy(perm + 1, "rwxrwxrwx");
	set_perm(mode, perm);
	return (perm);
}

void	ls_non_dir(int count, char **tab, int length, char flags[LEN_FL_LS])
{
	int				i;
	int				c_nonv;
	t_list			*lst;
	t_total			*total;

	lst = NULL;
	total = NULL;
	i = -1;
	ft_sorttab((void**)tab, count, &ft_strcmp);
	c_nonv = check_nonv(tab, count);
	i = c_nonv - 1;
	while (++i < count)
	{
		ft_lstadd(&lst, ft_lstnew(tab[i], ft_strlen(tab[i])));
		set_total(tab[i], &total);
	}
	ls_flags(lst, flags, total);
	if (count < length && count - c_nonv > 0)
		ft_printf("\n");
	ft_lstdel(&lst, &free_lst);
	free(total);
}

int		check_non_dir(char **tab, int length, char flags[LEN_FL_LS])
{
	int				i;
	int				count;
	struct stat		st;
	int				ret;

	count = 0;
	i = -1;
	while (++i < length)
	{
		if (is_flag_good('l', flags) == 1)
			ret = lstat(tab[i], &st);
		else
			ret = stat(tab[i], &st);
		if (ret == 0)
		{
			if ((st.st_mode & S_IFMT) != S_IFDIR)
				ft_swap_pt((void**)(tab + (count++)), (void**)(tab + i));
		}
		else
			ft_swap_pt((void**)(tab + (count++)), (void**)(tab + i));
	}
	if (count > 0)
		ls_non_dir(count, tab, length, flags);
	return (count);
}
