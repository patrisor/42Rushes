/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 22:46:53 by vbrazas           #+#    #+#             */
/*   Updated: 2019/08/18 13:18:58 by patrisor         ###   ########.fr       */
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

// Turns "grep" into "/usr/bin/grep"
static char		*get_binary_path(char cmd_name[], const t_pip *p)
{
	DIR				*d;
	struct dirent	*dir;
	char			*tmp;
	char			*joined;
	int				i;

	// iterate through our environmental "PATH=" variables (UNTIL command is found)
	i = 0;
	while (p->path[i])
	{
		// The opendir() function opens a directory stream corresponding to the
		// directory name, and returns a pointer to the directory stream.
		d = opendir(p->path[i]);
		// If the pointer returns a valid pid
		if (d)
			// Reads contents of the directory
			while ((dir = readdir(d)) != NULL)
				// Mathc the associated command name ("ls") with contents of this directory
				if (!ft_strcmp(dir->d_name, cmd_name))
				{
					// If it was found, it will close the directory stream
					closedir(d);
					// Places a "/" at the end of the path name
					tmp = ft_strjoin(p->path[i], "/");
					// Join once again with the name of the sys command
					joined = ft_strjoin(tmp, cmd_name);
					// Frees associated pointers
					free(tmp);
					free(cmd_name);
					return (joined);
				}
		// The closedir() function closes the directory stream
		closedir(d);
		i++;
	}
	// If no command was found, it will return NULL
	return (NULL);
}

// Creates a command array -> from "ls -l" into ["/usr/bin/ls","-l"]
char			**get_cmd_arr(char cmd[], const t_pip *p)
{
	static char		**cmd_arr = NULL;
	int				i;

	// Checks if the pointer to cmd_arr is already full, if so...
	if (cmd_arr != NULL) // CHECK
	{
		// Frees pointer contents and pointer itself
		i = 0;
		while (cmd_arr[i])
			free(cmd_arr[i++]);
		free(cmd_arr);
	}
	// This turns our sys calls ("ls -l") into ->(["ls", "-l"])
	cmd_arr = ft_strsplit(cmd, ' ');
	// Turns "grep" into "/usr/bin/grep"
	cmd_arr[0] = get_binary_path(cmd_arr[0], p);
	// returns ["/usr/bin/grep", "patrisor"]
	return (cmd_arr);
}
