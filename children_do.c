/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_do.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:55:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/18 18:17:10 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	child_one_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	char	**cmd_split;

	open_file_in(name, pipex);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		perror("dup2_stdin_child_one");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2_stdout_child_one");
	close_fd(pipex);
	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
		exit(1);
	if (ft_strchr(cmd_split[0], '/'))
	{
		exctract_args_address_one(cmd, pipex);
		if (access(pipex->cmd1_path, X_OK) != 0)
			acces_fail(pipex);
	}
	if (!pipex->cmd1_path)
		find_cmd1_path(cmd, env, pipex);
	execve(pipex->cmd1_path, pipex->cmd1_args, env);
	perror("execve");
	if (pipex->cmd1_path != pipex->cmd1_args[0])
		free(pipex->cmd1_path);
	free_array(pipex->cmd1_args);
	exit(1);
}

void	child_two_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	char	**cmd_split;

	open_file_out(name, pipex);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2_stdin_child_two");
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		perror("dup2_stdout_child_two");
	close_fd(pipex);
	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
		exit(1);
	if (ft_strchr(cmd_split[0], '/'))
	{
		exctract_args_address_two(cmd, pipex);
		if (access(pipex->cmd2_path, X_OK) != 0)
			acces_fail(pipex);
	}
	if (!pipex->cmd2_path)
		find_cmd2_path(cmd, env, pipex);
	execve(pipex->cmd2_path, pipex->cmd2_args, env);
	perror("execve");
	if (pipex->cmd2_path != pipex->cmd2_args[0])
		free(pipex->cmd2_path);
	free_array(pipex->cmd2_args);
	exit(1);
}
