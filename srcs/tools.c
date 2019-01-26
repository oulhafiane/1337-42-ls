/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:04:42 by zoulhafi          #+#    #+#             */
/*   Updated: 2018/11/30 11:02:41 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*set_path(char *real_path, char *path, char *name)
{
	ft_strcpy(real_path, path);
	ft_strcat(real_path, "/");
	ft_strcat(real_path, name);
	return (real_path);
}

int		is_hidden(char *path)
{
	int		i;

	i = 0;
	if (path[i] == '\0')
		return (1);
	while (path[++i] != '\0')
	{
		if (path[i - 1] == '/' && path[i] == '.')
			return (1);
	}
	return (0);
}

char	*get_file_name(char *p_file)
{
	int		i;

	i = -1;
	while (p_file[++i] != '\0')
	{
		if (p_file[i] == '/')
			return (get_file_name(p_file + i + 1));
	}
	return (p_file);
}

char	*get_uid(uid_t uid)
{
	struct passwd	*ret;

	if ((ret = getpwuid(uid)) != NULL)
		return (ret->pw_name);
	else
		return (ft_itoa(uid));
}

char	*get_gid(gid_t gid)
{
	struct group	*ret;

	if ((ret = getgrgid(gid)) != NULL)
		return (ret->gr_name);
	else
		return (ft_itoa(gid));
}
