/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:29:41 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/22 17:22:48 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error_giv();
	dup2(fd[1], STDOUT_FILENO);//end[1] or fd[1] to be execve stdout
	dup2(filein, STDIN_FILENO);//filein (file1) to be execve input
	close(fd[0]);//always close the end of the pipe I don't use. 
	//As long as it is open, the other end will wait for some kind of input and will not be able to finish its process 
	execution(argv[2], envp);
}

void	parent_proc(char **argv, char **envp, int *fd)
{
	int fileout;

	fileout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fileout == -1)
		error_giv();
	dup2(fd[0], STDIN_FILENO);//end[0] is the stdin
	dup2(fileout, STDOUT_FILENO);//file2 is the stdout
	close(fd[1]);
	execution(argv[3], envp);
}

int main(int argc, char **argv, char ** envp)
{
	int	fd[2];
	pid_t	pid1;

	if (argc ==  5)
	{
		if (pipe(fd) == -1)
			error_giv();
		pid1 = fork();
		if (pid1 == -1)
			error_giv();
		if (pid1 == 0)
			child_proc(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_proc(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Error: Wrong arguments\n", 2);
		ft_putstr_fd("Format is: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
