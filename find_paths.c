/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:12:59 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/18 17:01:05 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void find_cmd1_path(char *args1, char **env, t_pipex *pipex)
{
	int i;
	char **paths;
	
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
	i++;
	if (!env[i])
	{
		ft_putstr_fd(args1, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		exit(1);
	}
	pipex->cmd1_args = ft_split(args1, ' ');
	join_path_one(paths, pipex);
}

void join_path_one(char **paths, t_pipex *pipex)
{
	int i;
	i = 0;
	while (*paths && paths[i])
	{
		free(pipex->cmd1_path);
		pipex->cmd1_path = ft_strjoin3(paths[i], "/", pipex->cmd1_args[0]);
		if (access(pipex->cmd1_path, X_OK) == 0)
		{
			free_array(paths);
			return;
		}
		i++;
	}
	ft_putstr_fd(*pipex->cmd1_args, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_array(paths);
	free_array(pipex->cmd1_args);
	free(pipex->cmd1_path);
	exit(127);
}

void	find_cmd2_path(char *args2, char **env, t_pipex *pipex)
{
	int i;
	char **paths;
	
	i = 0;
	while (*env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putstr_fd(args2, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		exit(1);
	}
	pipex->cmd2_args = ft_split(args2, ' ');
	join_path_two(paths, pipex);
}

void	join_path_two(char **paths, t_pipex *pipex)
{
	int i;
	i = 0;
	while (*paths && paths[i])
	{
		free(pipex->cmd2_path);
		pipex->cmd2_path = ft_strjoin3(paths[i], "/", pipex->cmd2_args[0]);
		if (access(pipex->cmd2_path, X_OK) == 0)
		{
			free_array(paths);
			return;
		}
		i++;
	}
	ft_putstr_fd(*pipex->cmd2_args, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_array(paths);
	free_array(pipex->cmd2_args);
	free(pipex->cmd2_path);
	exit(127);
}
