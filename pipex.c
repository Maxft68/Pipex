/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/18 11:48:11 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void initialize(t_pipex *pipex, char **argv)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;
	
	if (!env || !*env)
		return (1);
	(void)argv;
	if (argc != 5)
		return (ft_putstr_fd("Use: ./pipex infile cmd1 cmd2 outfile\n", 2), 1);
	initialize(&pipex, argv);
	if (pipe(pipex.pipe_fd) == -1)
		return (perror("pipe"), 1);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_one_do(argv[1], argv[2], &pipex, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_two_do(argv[4], argv[3], &pipex, env);
	close_fd(&pipex);
	int status;
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &status, 0);
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return 1;
}


void join_path_one(char **paths, t_pipex *pipex)
{
	int i;
	i = 0;
	while (paths[i])
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


char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *s4;
	char *s5;
	
	s4 = ft_strjoin(s1, s2);
	s5 = ft_strjoin(s4, s3);
	free(s4);
	
	return(s5);
}


void	free_array(char **array)
{
	int	i;

	if (!array)
	return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return ;
}

void	close_fd(t_pipex *pipex)
{
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
}


void open_file_in(char *name, t_pipex *pipex)
{
	if (pipex->infile && access(pipex->infile, F_OK | R_OK) == -1)
	{
		perror(pipex->infile);
		close_fd(pipex);
		exit(127);
	}
	pipex->infile_fd = open(name, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror(name);
		exit(1);
	}
}
void open_file_out(char *name, t_pipex *pipex)
{
	pipex->outfile_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror(name);
		close_fd(pipex);
		exit(1);
	}
}
