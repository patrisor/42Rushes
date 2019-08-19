/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 20:20:30 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/18 22:23:38 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int				die(char *reason)
{
	ft_printf("%s\n", reason);
	return(-1);
}

char			**getPath(char **env)
{
	char		**path;

	while (*env != NULL && !ft_strnequ(*env, "PATH=", 5))
		(*env)++;
	if (*env == NULL)
		return(NULL);
	path = ft_strsplit(*env + 5, ':');
	return (path);
}

char            **getCommand(char a[], const t_pip *p)
{
	char			**ret;
	DIR				*d;
	struct dirent	*dir;
	int				i;

	ret = ft_strsplit(a, ' ');
	i = -1;
	while(p->path[++i])
	{
		d = opendir(p->path[i]);
		if (d)
			while ((dir = readdir(d)) != NULL)
				if (!ft_strcmp(dir->d_name, ret[0]))
				{
					closedir(d);
					ret[0] = ft_strjoin(ft_strjoin(p->path[i], "/"), ret[0]);
					return(ret);
				}
		closedir(d);
	}
	return(NULL);
}
