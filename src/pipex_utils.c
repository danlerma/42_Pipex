/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:57:00 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 12:57:06 by dlerma-c         ###   ########.fr       */
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

void	check_argv(char **paths, char ***argv, int argc)
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
		make_process(argv, aux, argc);
		i++;
		free(aux);
		if (paths[i])
		{
			temp = ft_strdup(paths[i]);
			aux = ft_strjoin(temp, "/");
			//printf("AUX: %s\n", aux);
			free(temp);
		}
	}
}

char	***new_agrv(int argc, char **argv)
{
	char	***new;
	int		i;

	i = 0;
	new = ft_calloc(argc, sizeof(char **));
	while (argv[i])
	{
		if (ft_strchr(argv[i], ' ') != NULL)
			new[i] = ft_split(argv[i], ' ');
		else
		{
			new[i] = ft_calloc(2, sizeof(char *));
			new[i][0] = ft_strdup(argv[i]);
		}
		i++;
	}
	return (new);
}
