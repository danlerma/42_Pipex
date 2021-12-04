/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:03:22 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 12:41:01 by dlerma-c         ###   ########.fr       */
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
	char		***n_argv;

	atexit(leaks);
	paths = find_path(environ);
	if (paths == NULL)
		return (0);	
	if (argc == 5)
	{
		printf("%s\n", paths[0]);
		printf("%s\n", paths[1]);
		printf("%s\n", paths[2]);
		printf("%s\n", paths[3]);
		printf("%s\n", paths[4]);
		printf("%s\n", paths[5]);
		printf("%s\n", paths[6]);
		n_argv = new_agrv(argc, argv);
		ft_free(argc, n_argv);
		//ft_free(argc, n_argv);
		//free(n_argv);
		check_argv(paths, argv);
		ft_free_malloc(paths);
	}
	else //NO PARA BOONUS
		ft_print_errors("ARGUMENTOS MAL INTRODUCIDOS\n");
	return (0);
}
