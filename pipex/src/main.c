/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:43:17 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/18 22:44:59 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int				main(int argc, char **argv, char **envp)
{
	t_pip	p;

	if (argc < 5)
		return(die("usage: ./pipex file1 cmd1 cmd2 file2"));
	if ((initPipe(&p, argv, envp) == -1) || (forkMe(&p, 0, argv, envp) == -1 || 
				forkMe(&p, 1, argv, envp) == -1) || (cleanPipe(&p) == -1))
		return(die(strerror(errno)));
	return(0);
}
