/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:54:54 by patrisor          #+#    #+#             */
/*   Updated: 2019/08/16 13:59:10 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// TEST ENVIRONMENTAL VARIABLES IN C
int main(int argc, char *argv[], char *envp[])
{
    while(*envp)
        printf("%s\n",*envp++);
}
