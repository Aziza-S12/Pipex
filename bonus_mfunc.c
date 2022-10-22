/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:18:19 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/22 17:15:25 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_p(char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1) // creating pipe and fork in a chile process
		error_giv();
	pid = fork();
	if (pid == -1)
		error_giv();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execution(*argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}//put output inside the pipe and close by execution. Main process will change its stdin for a pipe's fd.

/*Making a child process which will read from the stdin with gnl until it finds the limiter and after
put the output inside the pipe. The main process will change its stdin for pipe's fd */
void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		errors();
	if (pipe(fd) == -1)
		error_giv();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

char	*cmd_path(char *argv, char **envp)
{
	char	*env_path;
	char	*cmd_path;
	char	**paths;
	char	*keep;
	int		i;

	env_path = path_finding(envp, -1);
	paths = ft_split(env_path, ':');
	i = -1;
	while (paths[++i])
	{
		keep = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(keep);
	}
	i = -1;
	while (paths[++i]) //while there is a path to test
	{
		cmd_path = ft_strjoin(paths[i], argv); //add our command to the end
		if (access(cmd_path, F_OK | X_OK) == 0) //test if the path is accessible and executable
			return (cmd_path); // if true - we've found the correct path
		free (cmd_path);
	}
	return(cmd_path);
}

char	*path_finding(char **envp, int i)
{
	char	*env_path;

	env_path = NULL;
	while(envp[++i]) //loop in envp to find the line that starts with "PATH="
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break;
		}
	}
	return (env_path);
}

/*Runs the childs proc with correct fd or displays an error msg if wrong args.
Runs the here_doc func if the here_doc string is found in argv[1] */
int main(int argc, char **argv, char **envp)
{
	int	file1;
	int	file2;
	int	i;

	if (argc >= 5)
	{
		if(ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			file2 = open_f(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			file2 = open_f(argv[argc - 1], 1);
			file1 = open_f(argv[1], 2);
			dup2(file1, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_p(&argv[i++], envp);
		dup2(file2, STDOUT_FILENO);
		execution(argv[argc - 2], envp);
	}
	errors();
}
