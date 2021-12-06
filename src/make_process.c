/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:17:33 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/06 13:55:45 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	make_command(t_commands *command, char *com, int i, char **environ)
{
	pid_t	child;

	if (command->fd_pipe)
		free(command->fd_pipe);
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
		dup2(command->fd_pipe[1], STDOUT_FILENO);
		close(command->fd_pipe[1]);
		execve(com, command->argv[i], environ);
	}
	else
	{
		wait(&child);
		close(command->fd_pipe[1]);
		dup2(command->fd_pipe[0], STDIN_FILENO);
		close(command->fd_pipe[0]);
	}
}

void	make_process(t_commands *command, char **environ)
{
	int		i;
	int		j;
	char	*com;

	check_infile(command);
	i = 2;
	while (i <= (command->num_comds + 1))
	{
		j = 0;
		while (command->paths[j])
		{
			com = ft_strjoin(command->paths[j], command->argv[i][0]);
			if (access(com, X_OK) == 0 && i == (command->num_comds + 1))
				break ;
			if (access(com, X_OK) == 0)
				make_command(command, com, i, environ);
			free(com);
			j++;
		}
		i++;
	}
	check_outfile(command, i, com, environ);
}
