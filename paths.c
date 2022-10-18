/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:23:55 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/18 19:48:43 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_finding(char **envp, int i)
{
	char	*env_path;

	env_path = NULL;
	i = 0; 
	while(envp[i]) //loop in envp to find the line that starts with "PATH="
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break;
		}
	}
	i++;
	return (env_path);
}

char	*command_path(char *argv, char **envp)
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
		cmd_path = ft_split(paths[i], argv); //add our command to the end
		if (access(cmd_path, F_OK | X_OK) == 0) //test if the path is accessible and executable
			return (cmd_path); // if true - we've found the correct path
		free (cmd_path);
	}
	return(cmd_path);
}

// int main(int argc, char **argv, char**envp)
// {
// 	char	*cmd_path;
// 	char	*options[3] = {"ls", "-la", NULL};
// 	char	*cmd = "ls";

// 	(void)argc;
// 	(void)argv;
// 	cmd_path = get_cmd_path(cmd, envp);

// 	if (!cmd_path)
// 	{
// 		perror(cmd_path);
// 		return(-1);
// 	}
// 	execve(cmd_path, options, envp);
// 	printf("It works!");
// 	free(cmd_path);
// 	return (0);
// }