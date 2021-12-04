/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:17:33 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 15:44:14 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	make_pipe(t_commands *command, char *com, int i, char **environ)
{
	pid_t	child;

	printf("--> %s  %s\n", command->argv[i][0], command->argv[i][1]);
	command->fd_pipe = (int *)ft_calloc(2, sizeof(int));
	if (command->fd_pipe == NULL)
		ft_print_errors("CREATING PIPES\n");
	pipe(command->fd_pipe);
	child = fork();
	if (child < 0 || command->fd_pipe < 0)
		ft_print_errors("FAIL CREATING PROCESS\n");
	if (child == 0)
	{
		close(command->fd_pipe[0]);
		printf("HIJO -> %d\n", child);
		dup2(command->fd_pipe[1], STDOUT_FILENO);
		close(command->fd_pipe[1]);
		execve(com, command->argv[i], environ);
	}
	else
		wait(&child);
}
