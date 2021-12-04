/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 14:08:15 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define PATH_ENV "PATH"

# include <libft.h>
# include <stdio.h>
# include <unistd.h>

char	**find_path(char **environ);
void	check_argv(char **paths, char ***argv, int argc, char **environ);
void	check_permision(char *file, char per);
void	make_process(char ***argv, char *aux, int argc, char **environ);
char	***new_agrv(int argc, char **argv);

#endif
