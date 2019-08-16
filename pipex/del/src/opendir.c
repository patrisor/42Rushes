/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 22:46:53 by vbrazas           #+#    #+#             */
/*   Updated: 2019/08/16 14:04:46 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// Grabs list of Environmental Variables and finds the "PATH=" String.
// RETURNS: ["/usr/local/bin", "/usr/bin", "/bin", "/usr/sbin", "/sbin", 
// "/opt/X11/bin", "/Library/Frameworks/Mono.framework/Versions/Current/Commands", 
// "/usr/local/munki", "/nfs/2018/p/patrisor/.rvm/bin"] 
// Environment variables are a set of dynamic named values that can affect the 
// way running processes will behave on a computer.
char			**get_path(char **env)
{
	char		**path;

	while (*env != NULL && !ft_strnequ(*env, "PATH=", 5))
		(*env)++;
	(*env == NULL) ? put_usage(2) : false;
	path = ft_strsplit(*env + 5, ':');
	return (path);
}

static char		*get_binary_path(char cmd_name[], const t_pip *p)
{
	DIR				*d;
	struct dirent	*dir;
	char			*tmp;
	char			*joined;
	int				i;

	i = 0;
	while (p->path[i])
	{
		d = opendir(p->path[i]);
		if (d)
			while ((dir = readdir(d)) != NULL)
				if (!ft_strcmp(dir->d_name, cmd_name))
				{
					closedir(d);
					tmp = ft_strjoin(p->path[i], "/");
					joined = ft_strjoin(tmp, cmd_name);
					free(tmp);
					free(cmd_name);
					return (joined);
				}
		closedir(d);
		i++;
	}
	return (NULL);
}

char			**get_cmd_arr(char cmd[], const t_pip *p)
{
	static char		**cmd_arr = NULL;
	int				i;

	if (cmd_arr != NULL)
	{
		i = 0;
		while (cmd_arr[i])
			free(cmd_arr[i++]);
		free(cmd_arr);
	}
	cmd_arr = ft_strsplit(cmd, ' ');
	cmd_arr[0] = get_binary_path(cmd_arr[0], p);
	return (cmd_arr);
}
