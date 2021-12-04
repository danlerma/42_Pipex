/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 15:34:40 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define PATH_ENV "PATH"

# include <libft.h>
# include <stdio.h>
# include <unistd.h>

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
void	check_argv(char **paths, t_commands *command, char **environ);
void	check_permision(char *file, char per);
void	make_process(char ***argv, char *aux, int argc, char **environ);
char	***new_agrv(int argc, char **argv);
void	make_pipe(t_commands *command, char *com, int i, char **environ);

#endif
