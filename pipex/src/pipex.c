/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 20:35:11 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/18 22:40:55 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int		cleanPipe(t_pip *p)
{
	if (close(p->fd[0][0]) == -1 || close(p->fd[0][1]) == -1 ||
			close(p->fd[1][0]) == -1 || close(p->fd[1][1]) == -1)
		return(-1);
	while (wait(NULL) > 0) ;
	return(0);
}

int		initPipe(t_pip *p, char **a, char **e)
{
	if ((pipe((*p).pair)) == -1)
		return(-1);
	(*p).fd[0][0] = open(a[1], O_RDONLY);
	(*p).fd[0][1] = (*p).pair[1];
	(*p).fd[1][0] = (*p).pair[0];
	(*p).fd[1][1] = open(a[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if ((*p).fd[0][0] == -1 || (*p).fd[1][1] == -1)
		return(-1);
	if ((p->path = getPath(e)) == NULL)
		return(die("Cannot find binary of the given command"));
	return(0);
}

int		forkMe(t_pip *p, int i, char **a, char **e)
{
	char	**cmd;

	cmd = getCommand(a[2 + i], p);
	if ((p->pid = fork()) == -1)
		return(-1);
	if (p->pid == 0)
	{
		if ((dup2(p->fd[i][0], 0) == -1) || (dup2(p->fd[i][1], 1) == -1) || 
				(close(p->fd[!(i % 2)][0]) == -1) || (close(p->fd[!(i % 2)][1]) == -1) 
				|| (execve(cmd[0], cmd, e) == -1))
			return(-1);
	}
	return (0);
}
