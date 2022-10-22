/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:30:32 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/22 18:03:58 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MAX_FD 1023

# include "libft/libft.h"
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

/*Bonus part*/
void	child_p(char **argv, char **envp);
void	here_doc(char *limiter, int argc);
int		open_f(char *argv, int i);
void	errors(void);
int		get_next_line(char **line);

#endif