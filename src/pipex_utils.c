/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:57:00 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/11/30 19:44:53 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**find_path(char **environ)
{
	int		i;
	char	**paths;
	char	*pos;

	i = 0;
	paths = NULL;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], PATH_ENV, 4) == 0)
		{
			pos = ft_strchr(environ[i], '=');
			paths = ft_split(pos + 1, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

void	make_process(char **argv, char *aux)
{
	int		i;
	char	*command;

	i = 2;
	while (argv[i])
	{
		command = ft_strjoin(aux, argv[i]);
		if (access(command, X_OK) == 0)
			printf("TIENE PERMISO: %s\n", command);
		i++;
		free(command);
	}
}

void	check_argv(char **paths, char **argv)
{
	int		i;
	char	*aux;
	char	*temp;

	i = 0;
	temp = ft_strdup(paths[i]);
	aux = ft_strjoin(temp, "/");
	free(temp);
	while (paths[i])
	{
		make_process(argv, aux);
		i++;
		free(aux);
		if (paths[i])
		{
			temp = ft_strdup(paths[i]);
			aux = ft_strjoin(temp, "/");
			free(temp);
		}
	}
}
