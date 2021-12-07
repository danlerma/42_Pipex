/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:23:09 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/07 22:31:42 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	make_heredoc(t_commands *command, char *com, int i, char **environ)
{
	pid_t	child;
	char	*line;

	pipe(command->fd_pipe);
	printf("PADRE: %d\n", getpid());
	child = fork();
	if (child < 0 || command->fd_pipe < 0)
		ft_print_errors("FAIL CREATING PROCESS\n");
	if (child == 0)
    {
		printf("HIJO: %d\n", getpid());
        while (1)
        {
            line = get_next_line(STDIN_FILENO);
		    if (ft_strncmp(line, "hola", 4) == 0
			    && (ft_strlen(line) - 1) == 4)
		    {
			    //printf("ESTA ES LA LINEA LIMITADORA LINE ----> %s", line);
                close(command->fd_pipe[1]);
			    free(line);
				printf("estoy muerto\n");
			    exit(0);
		    }
        	close(command->fd_pipe[0]);
            write(command->fd_pipe[1], line, ft_strlen(line));
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
	printf("TERMINË\n");
}

// void	delete_file(t_commands *command, char **environ)
// {
// 	int	child;
// 	char	**comnd;

// 	comnd = ft_calloc(2, sizeof(char *));
// 	if (comnd == NULL)
// 		ft_print_errors("FAIL CREATING MALLOC\n");
// 	comnd[0] = (char *)ft_calloc(2, sizeof(char));
// 	comnd[0] = "rm";
// 	comnd[1] = (char *)ft_calloc(3, sizeof(char));
// 	comnd[1] = "-rf";
// 	child = fork();
// 	if (child == 0)
// 	{
// 		printf("SALIDA HIJO -> %d\t%s %s\n", getpid(), comnd[0], comnd[1]);
// 		command->fd_in = open(command->argv[1][0], O_RDWR);
// 		dup2(command->fd_in, STDIN_FILENO);
// 		//close(command->fd_in);
// 		execve("/bin/rm", comnd, environ);
// 	}
// 	else
// 	{
// 		wait(&child);
// 		free(comnd);
// 		printf("terminado\n");
// 	}
// }

void	heredoc(t_commands *command, char **environ)
{
	int		i;
	int		pos;
	int		j; 
	char	*com;

	printf("---> LIMITADOR %s\n", command->argv[2][0]);
	check_heardoc(command);
	make_heredoc(command, com, pos, environ);
	command->num_comds--;
	i = 1;
	pos = 3;
	while (i <= command->num_comds)
	{
		j = 0;
		while (command->paths[j])
		{
			//printf("---> %d COMAND ARGV %s\n", command->num_comds, command->argv[pos][0]);
			com = ft_strjoin(command->paths[j], command->argv[pos][0]);
			if (access(com, X_OK) == 0 && i == (command->num_comds))
				break ;	
			else if (access(com, X_OK) == 0)
			{
				printf("ACCES %s  %d\n", com, i);
				make_command(command, com, pos, environ);
			}
			free(com);
			j++;
		}
		pos++;
		i++;
	}
	check_outfile(command, pos, com, environ);
	//delete_file(command, environ);
}
