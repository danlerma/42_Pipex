/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:13:37 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/07 14:35:34 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	check_heardoc(t_commands *command)
{
	if (command->fd_pipe)
		free(command->fd_pipe);
	command->fd_pipe = (int *)ft_calloc(2, sizeof(int));
	if (command->fd_pipe == NULL)
		ft_print_errors("CREATING PIPES\n");
}

void	check_infile(t_commands *command)
{
	command->fd_in = open(command->argv[1][0], O_RDONLY);
	if (command->fd_in < 0)
		ft_print_errors("FAIL OPENING FILE\n");
	dup2(command->fd_in, STDIN_FILENO);
	close(command->fd_in);
}

void	check_outfile(t_commands *command, int i, char *out, char **environ)
{
	int	child;

	child = fork();
	if (child == 0)
	{
		printf("SALIDA HIJO -> %d\n", getpid());
		command->fd_out = open(command->argv[command->argc - 1][0],
				O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(command->fd_out, STDOUT_FILENO);
		close(command->fd_out);
		execve(out, command->argv[i - 1], environ);
	}
	else
	{
		wait(&child);
		free(out);
		printf("terminado\n");
	}
}
