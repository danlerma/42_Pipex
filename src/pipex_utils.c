/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:57:00 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 16:04:16 by dlerma-c         ###   ########.fr       */
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

void	check_infile(t_commands *command)
{
	//Abro el infile
	command->fd_in = open(command->argv[1][0], O_RDONLY);
	if (command->fd_in < 0)
		ft_print_errors("FAIL OPENING FILE\n");
	dup2(command->fd_in, STDIN_FILENO);
	close(command->fd_in);
	////////////////////////
}

void	check_outfile(t_commands *command, int i, char *out, char **environ)
{
	int	child;

	printf("pppppp->>> %s  %s\n", out, command->argv[i - 1][1]);
	child = fork();
	if (child == 0)
	{
		command->fd_out = open("salida.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(command->fd_out , STDOUT_FILENO);
		close(command->fd_out );
		execve(out, command->argv[i - 1], environ);
	}
	else
	{
		wait(&child);
		free(out);
		printf("terminado\n");
	}
}

void	check_argv(char **paths, t_commands *command, char **environ)
{
	int		i;
	int		j;
	char	*com;
	char	*out;

	com = NULL;
	valid_path(paths, command);
	//Abro el infile
	check_infile(command);
	i = 2;
	while (i <= (command->num_comds + 1))
	{
		j = 0;
		while (command->paths[j])
		{
			if (i == command->num_comds + 1)
			{
				out = ft_strjoin(command->paths[j], command->argv[i][0]);
				if (access(out, X_OK) == 0)
					break;
				free(out);
			}
			com = ft_strjoin(command->paths[j], command->argv[i][0]);
			if (access(com, X_OK) == 0)
			{
				make_pipe(command, com, i, environ);
				printf("HIJO TERMINADO\n");
				close(command->fd_pipe[1]);
				dup2(command->fd_pipe[0], STDIN_FILENO);
				close(command->fd_pipe[0]);
			}
			free(com);
			j++;
		}
		i++;
	}
	//SALIDA DEL PROCESO
	check_outfile(command, i, out, environ);
	//com = ft_strjoin(command->paths[j], command->argv[i][0]);
	
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
