/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:57:00 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 15:20:00 by dlerma-c         ###   ########.fr       */
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

static void valid_path(char **paths, t_commands *command)
{
	int		i;
	char	*aux;

	i = 0;
	while (paths[i])
		i++;
	command->paths = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	aux = ft_strdup(paths[i]);
	command->paths[i] = ft_strjoin(aux, "/");
	free(aux);
	while (paths[i])
	{
		i++;
		if (paths[i])
		{
			aux = ft_strdup(paths[i]);
			command->paths[i] = ft_strjoin(aux, "/");
			free(aux);
		}
	}
}

void	check_file(t_commands *command)
{
	//Abro el infile
	command->fd_in = open(command->argv[1][0], O_RDONLY);
	if (command->fd_in < 0)
		ft_print_errors("FAIL OPENING FILE\n");
	dup2(command->fd_in, STDIN_FILENO);
	close(command->fd_in);
	////////////////////////
}

void	check_argv(char **paths, t_commands *command, char **environ)
{
	int	i;
	int	j;
	char	*com;

	(void) environ;
	valid_path(paths, command);
	//Abro el infile
	check_file(command);
	i = 2;
	while (i <= command->num_comds)
	{
		j = 0;
		while (command->paths[j])
		{
			com = ft_strjoin(command->paths[j], command->argv[i][0]);
			if (access(com, X_OK) == 0)
			{
				printf("command : %s\n", com);
			}
			free(com);
			j++;
		}
		i++;
	}
	//SALIDA DEL PROCESO

	/////////////////////
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
