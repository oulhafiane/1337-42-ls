/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:04:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:10:09 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_flags(t_list *lst, char flags[LEN_FL_LS], t_total *total)
{
	if (is_flag_good('t', flags))
		ft_lstsort(&lst, &cmp_files_bytime);
	else
		ft_lstsort(&lst, &cmp_files);
	if (is_flag_good('r', flags))
		ft_lstrev(&lst);
	if (is_flag_good('l', flags))
		ls_print_l(lst, total);
	else
		ft_lstcontent_iter(lst, &print_one_file);
	if (is_flag_good('R', flags))
		ls_with_bigr(lst, flags);
}

void	ft_ls(char *path, char flags[LEN_FL_LS])
{
	DIR				*current;
	struct dirent	*dp;
	t_list			*lst;
	char			real_path[1024];
	t_total			*total;

	if ((current = check_permission(path)) == NULL)
		return ;
	lst = NULL;
	total = NULL;
	while ((dp = readdir(current)) != NULL)
	{
		set_path(real_path, path, dp->d_name);
		if (is_hidden(real_path) == 0 || is_flag_good('a', flags) == 1)
		{
			ft_lstadd(&lst, ft_lstnew(real_path, ft_strlen(real_path) + 1));
			set_total(real_path, &total);
		}
	}
	closedir(current);
	if (is_flag_good('l', flags) && lst != NULL)
		ft_printf("total %d\n", total->total);
	ls_flags(lst, flags, total);
	ft_lstdel(&lst, &free_lst);
	free(total);
}

void	iter_args(int argc, char **argv, int index, char flags[LEN_FL_LS])
{
	int		old_index;
	int		inside;
	int		i;

	old_index = index;
	index += check_non_dir(argv + index, argc - index, flags);
	if (is_flag_good('t', flags) == 1)
		ft_sorttab((void**)(argv + index), argc - index, &cmp_bytime);
	else
		ft_sorttab((void**)(argv + index), argc - index, &ft_strcmp);
	if (is_flag_good('r', flags) == 1)
		ft_revtab((void**)(argv + index), argc - index);
	i = index - 1;
	inside = 0;
	while (++i < argc)
	{
		if (inside == 1)
			ft_printf("\n");
		if ((argc - old_index) > 1)
			ft_printf("%s:\n", argv[i]);
		ft_ls(argv[i], flags);
		inside = 1;
	}
}

int		main(int argc, char **argv)
{
	char	flags[LEN_FL_LS];
	int		index;
	int		i;

	index = get_flags_ls(argc, argv, flags);
	if (index == -1)
		return (1);
	i = index - 1;
	while (++i < argc)
		if (argv[i][0] == '\0')
		{
			ft_fprintf(2, "ls: fts_open: No such file or directory\n");
			return (1);
		}
	if (index == 0 || index == argc)
		ft_ls(".", flags);
	else
		iter_args(argc, argv, index, flags);
	return (0);
}
