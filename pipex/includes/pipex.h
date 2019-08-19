/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:35:46 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/18 21:53:23 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_pipex
{
	int			pair[2];
	int			fd[2][2];
	pid_t		pid;
	char		**path;
}				t_pip;

/* ******************** AUX ******************** */
char	**getPath(char **env);
char	**getCommand(char a[], const t_pip *p);
int		die(char *reason);
/* ******************* PIPEX ******************* */
int		initPipe(t_pip *p, char **a, char **e);
int		cleanPipe(t_pip *p);
int     forkMe(t_pip *p, int i, char **a, char **e);

#endif
