/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:03:22 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 15:53:20 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	leaks(void)
{
	system("leaks -q pipex");
}

static void	ft_free( int argc, char ***str)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ft_free_malloc(str[i]);
		i++;
	}
	free(str);
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
	if (argc <= 6)
	{
		command->argv = new_agrv(argc, argv);
		check_argv(paths, command, environ);
		ft_free(argc, command->argv);
		ft_free_malloc(command->paths);
		ft_free_malloc(paths);
		free(command->fd_pipe);
		free(command);
	}
	else //NO PARA BOONUS
		ft_print_errors("ARGUMENTOS MAL INTRODUCIDOS\n");
	return (0);
}
