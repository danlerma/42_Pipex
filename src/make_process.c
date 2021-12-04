/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:17:33 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 12:56:59 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	make_process(char ***argv, char *aux, int argc)
{
	int		i;
	char	*command;

	i = 2;
	while (i < (argc - 1))
	{
		command = ft_strjoin(aux, argv[i][0]);
		if (access(command, X_OK) == 0)
		{
			printf("command : %s\n", command);
			//make_pipe(command);
		}
		i++;
		free(command);
	}
}
