/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:23:55 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/17 17:38:33 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*path_finding(char **envp, int i)
{
	char	*env_path;

	env_path = NULL;
	while(envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break;
		}
	}
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
	while (paths[++i])
	{
		cmd_path = ft_split(paths[i], argv);
		if (!(access(cmd_path, F_OK | X_OK)))
			break;
		free (cmd_path);
	}
	return(cmd_path);
}