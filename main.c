/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:29:41 by asadritd          #+#    #+#             */
/*   Updated: 2022/10/13 15:19:23 by asadritd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execve(const char *pathname, char *const argv[], char *const envp[])
{
	
}

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
