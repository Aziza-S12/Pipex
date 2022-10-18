/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:29:41 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/18 19:48:17 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char ** envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid;
	int 	i;

	if (argc < 5 || envp == 0)
		return (printf("Error! The format is incorrect"));
	i = 0;
}