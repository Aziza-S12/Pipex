/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:42:13 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/22 17:14:42 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_f(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error_giv();
	return (file);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	j = read(0, &c, 1);
	while (j && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		j = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (j);
}

void	execution(char *argv, char **envp)
{
	char	**cmnd;
	char	*path;
	int		i;

	i = -1;
	cmnd = ft_split(argv, ' ');
	path = cmd_path(cmnd[0], envp);
	if (!path)
	{
		while (cmnd[++i])
			free(cmnd[i]);
		free(cmnd);
		error_giv();
	}
	if (execve(path, cmnd, envp) == -1)
		error_giv();
}

void	error_giv(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	errors(void)
{
	ft_putstr_fd("Error: Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_SUCCESS);
}
