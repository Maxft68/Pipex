/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/18 17:06:11 by mdsiurds         ###   ########.fr       */
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




