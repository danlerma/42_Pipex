/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:23:09 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/01/10 19:02:31 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	limit(t_commands *command, int len, char *line)
{
	if (ft_strncmp(line, command->argv[2][0], len) == 0
		&& ((int)ft_strlen(line) - 1) == len)
	{
		close(command->fd_pipe[1]);
		free(line);
		exit(0);
	}
	close(command->fd_pipe[0]);
	write(command->fd_pipe[1], line, ft_strlen(line));
}

void	make_heredoc(t_commands *command)
{
	pid_t	child;
	char	*line;
	int		len;

	pipe(command->fd_pipe);
	child = fork();
	if (child < 0 || command->fd_pipe < 0)
		ft_print_errors("FAIL CREATING PROCESS\n");
	len = ft_strlen(command->argv[2][0]);
	if (child == 0)
	{
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			limit(command, len, line);
			free(line);
		}
	}
	else
	{
		close(command->fd_pipe[1]);
		dup2(command->fd_pipe[0], STDIN_FILENO);
		close(command->fd_pipe[0]);
		wait(&child);
	}
}

void	heredoc(t_commands *command, char **environ)
{
	int		i;
	int		pos;
	int		j;
	char	*com;

	i = 1;
	pos = 3;
	check_heardoc(command);
	while (i <= command->num_comds)
	{
		j = 0;
		while (command->paths[j])
		{
			com = ft_strjoin(command->paths[j], command->argv[pos][0]);
			if (access(com, X_OK) == 0 && i == (command->num_comds))
				break ;
			else if (access(com, X_OK) == 0)
				make_command(command, com, pos, environ);
			free(com);
			j++;
		}
		pos++;
		i++;
	}
	check_outfile(command, pos, com, environ);
}
