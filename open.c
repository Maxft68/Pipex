/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:17:23 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/18 17:38:01 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		close_fd(pipex);
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