/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:32:30 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/14 18:16:43 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> // pour fork, pipe, execve, etc.
#include <stdlib.h> // pour malloc, free, exit
#include <stdio.h> // pour perror
#include <fcntl.h> // pour open, O_RDONLY, etc.
#include <errno.h>
#include <sys/wait.h> // pour waitpid
# include "./libft/libft/libft.h"
# include "./libft/printf/ft_printf.h"

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
	int		pipe_fd[2];// Descripteurs du pipe [0]=lecture, [1]=écriture
	int		pid1;
	int		pid2;
}			t_pipex;

void	initialize(t_pipex *pipex);
void	debug_print_pipex(t_pipex *pipex); //a degager a la fin


#endif
