/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:03:22 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/11/30 19:35:05 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	leaks(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	char		**paths;

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
		check_argv(paths, argv);
	}
	else //NO PARA BOONUS
		ft_print_errors("ARGUMENTOS MAL INTRODUCIDOS\n");
	leaks();
	return (0);
}
