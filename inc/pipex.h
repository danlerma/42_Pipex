/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/12/04 12:26:27 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define PATH_ENV "PATH"

# include <libft.h>
# include <stdio.h>
# include <unistd.h>

char	**find_path(char **environ);
void	check_argv(char **paths, char **argv);
void	check_permision(char *file, char per);
void	make_process(char **argv, char *aux);
char	***new_agrv(int argc, char **argv);

#endif
