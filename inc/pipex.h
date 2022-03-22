/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/03/22 08:14:09 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define PATH_ENV "PATH"
# define HERE_DOC "here_doc"

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_commands
{
	int		argc;
	int		num_comds;
	char	***argv;
	char	**paths;
	int		*fd_pipe;
	int		fd_in;
	int		fd_out;
}	t_commands;

char	**find_path(char **environ);
void	valid_path(char **paths, t_commands *command);
char	***new_agrv(int argc, char **argv);
//make_process.c
void	make_process(t_commands *command, char **environ);
void	make_command(t_commands *command, char *com, int i, char **environ);
//check_files.c
void	check_infile(t_commands *command);
void	check_outfile(t_commands *command, int i, char *out, char **environ);
void	check_heardoc(t_commands *command);
//heredoc.c
void	heredoc(t_commands *command, char **environs);
void	make_heredoc(t_commands *command);

#endif
