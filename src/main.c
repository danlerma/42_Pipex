/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:03:22 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 16:40:16 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	leaks(void)
{
	system("leaks -q pipex");
}

static void	ft_free( int argc, char ***str, t_commands *command, char **paths)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ft_free_malloc(str[i]);
		i++;
	}
	free(str);
	ft_free_malloc(command->paths);
	free(command->fd_pipe);
	ft_free_malloc(paths);
	free(command);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	char		**paths;
	t_commands	*command;

	atexit(leaks);
	paths = find_path(environ);
	if (paths == NULL)
		return (0);
	command = ft_calloc(1, sizeof(t_commands));
	command->argc = argc;
	command->num_comds = argc - 3;
	if (argc >= 5)
	{
		command->argv = new_agrv(argc, argv);
		valid_path(paths, command);
		//si estamos en heredoc
		if (ft_strncmp(argv[1], HERE_DOC, sizeof(HERE_DOC)) == 0)
			heredoc(command);
		else
			make_process(command, environ);
		ft_free(argc, command->argv, command, paths);
	}
	else
		ft_print_errors("ARGUMENTOS MAL INTRODUCIDOS\n");
	return (0);
}
