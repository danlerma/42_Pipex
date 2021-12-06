/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:23:09 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/06 13:51:18 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	heredoc(t_commands *command, char **environ)
{
	int		i;
	int		pos;
	int		j;
	char	*com;
	// ./pipex here\_doc LIMITADOR comando comando1 archivo
	//la entrada va a ser stdin, entonces no la cmabiamos
	printf("---> LIMITADOR %s\n", command->argv[2][0]);
	command->num_comds--;
	i = 0;
	pos = 3;
	while (i < command->num_comds)
	{
		j = 0;
		while (command->paths[j])
		{
			//printf("---> %d COMAND ARGV %s\n", command->num_comds, command->argv[pos][0]);
			com = ft_strjoin(command->paths[j], command->argv[pos][0]);
			if (access(com, X_OK) == 0 && i == (command->num_comds + 1))
				break ;
			if (access(com, X_OK) == 0)
				make_command(command, com, i, environ);
			free(com);
			j++;
		}
		pos++;
		i++;
	}
}
