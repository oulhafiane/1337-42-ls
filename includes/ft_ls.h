/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:54:18 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:21:55 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define LEN_FL_LS 7
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>

typedef struct	s_total
{
	int			total;
	int			max_uid;
	int			max_gid;
	int			max_link;
	int			max_size;
}				t_total;

void			ft_ls(char *path, char flags[LEN_FL_LS]);
void			set_total(char *name, t_total **total);
char			*set_path(char *real_path, char *path, char *name);
int				check_non_dir(char **tab, int length, char flags[LEN_FL_LS]);
void			ls_flags(t_list *lst, char flags[LEN_FL_LS], t_total *total);
int				get_flags_ls(int argc, char **argv, char flags[LEN_FL_LS]);
int				is_flag_good(char flag, char *list_flags);
int				is_hidden(char *path);
char			*get_file_name(char *p_file);
char			*translate_mode(mode_t mode);
void			ls_print_l(t_list *lst, t_total *total);
void			ls_with_bigr(t_list *lst, char flags[LEN_FL_LS]);
void			print_one_file(void *name);
int				cmp_files(t_list *first, t_list *second);
int				cmp_files_bytime(t_list *first, t_list *second);
int				cmp_bytime(char *file1, char *file2);
void			free_lst(void *content, size_t size);
char			*get_uid(uid_t uid);
char			*get_gid(gid_t gid);
DIR				*check_permission(char *path);
int				check_nonv(char **tab, int count);

#endif
