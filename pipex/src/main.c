/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:43:17 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/18 15:50:40 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int		main(int argc, char **argv, char **envp)
{
	while(*argv)
		ft_printf("%d: %s\n", argc, *argv++);
	ft_printf("ENVIROVARIABLES\n\n\n\n");
	while(*envp)
		ft_printf("%s\n", *envp++);
	return(0);
}
