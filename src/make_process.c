/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:17:33 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 14:12:04 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

 void	child_process()
{
	
}

 pid_t	make_pipe(char **argv, char *command, char **environ)
{
	pid_t	child;
	int		*fd_pipe;
	
	printf("--> %s  %s\n", argv[0], argv[1]);
	fd_pipe = ft_calloc(2, sizeof(int));
	if (fd_pipe == NULL)
		ft_print_errors("CREATING PIPES\n");
	pipe(fd_pipe);
	child = fork();
	if (child < 0 || fd_pipe < 0)
		ft_print_errors("FAIL CREATING PROCESS\n");
	if (child == 0)
	{
		close(fd_pipe[0]);
		printf("HIJO -> %d\n", child);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		execve(command, argv, environ);
	}
	else
	{
		//paro el padre hasta que termine el hijo
		wait(&child);
	}
	return (0);
}

void	make_process(char ***argv, char *aux, int argc, char **environ)
{
	int		i;
	char	*command;
	int		fd;
	pid_t	child;
	i = 2;
	//Abro el infile
	fd = open(argv[1][0], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	////////////////////////
	while (i < (argc - 2))
	{
		command = ft_strjoin(aux, argv[i][0]);
		if (access(command, X_OK) == 0)
		{
			printf("command : %s\n", command);
			child = make_pipe(argv[i], command, environ);
			printf("TODOS LOS HIJOS TERMINADOS\n");	
		}
		i++;
		free(command);
	}
	
	//SALIDA DEL PROCESO

	/////////////////////
}
