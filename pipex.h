/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:30:32 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/20 18:32:43 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MAX_FD 1023

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

void	error_giv(void);
char	*path_finding(char **envp, int i);
char	*cmd_path(char *argv, char **envp);
void	execution(char *argv, char **envp);
void	parent_proc(char **argv, char **envp, int *fd);
void	child_proc(char **argv, char **envp, int *fd);

#endif