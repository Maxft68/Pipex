/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:32:30 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/17 23:46:28 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
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
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
}			t_pipex;

void	initialize(t_pipex *pipex, char **argv);
void	child_one_do(char *name, char *cmd, t_pipex *pipex, char **env);
void	child_two_do(char *name, char *cmd, t_pipex *pipex, char **env);
void	find_cmd1_path(char *args1, char **env, t_pipex *pipex);
void	find_cmd2_path(char *args2, char **env, t_pipex *pipex);
void	join_path_one(char **paths, t_pipex *pipex);
void	join_path_two(char **paths, t_pipex *pipex);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	exctract_args_address_one(char *cmd, t_pipex *pipex);
void	exctract_args_address_two(char *cmd, t_pipex *pipex);
void	open_file_in(char *name, t_pipex *pipex);
void	open_file_out(char *name, t_pipex *pipex);
void	free_array(char **array);
void	close_fd(t_pipex *pipex);

#endif
