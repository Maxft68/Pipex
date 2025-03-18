/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:48:14 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/18 11:48:28 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exctract_args_address_one(char *cmd, t_pipex *pipex)
{
	int i;
	char **args;
	char **split_args;
	
	i = 0;
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_array(args);
		perror(cmd);
		exit(1);
	}
	pipex->cmd1_path = ft_strdup(args[0]);
	split_args = ft_split(args[0], '/');
	while(split_args[i + 1])
	i++;
	pipex->cmd1_args = ft_split(cmd, ' ');
	free(pipex->cmd1_args[0]);
	pipex->cmd1_args[0] = ft_strdup(split_args[i]);
	free_array(split_args);
	if (args[1])
	{
		pipex->cmd1_args[1] = ft_strdup(args[1]);
	}
	free_array(args);
}

void  exctract_args_address_two(char *cmd, t_pipex *pipex)
{
	int i;
	char **args;
	char **split_args;
	
	i = 0;
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_array(args);
		perror(cmd);
		exit(1);
	}
	pipex->cmd2_path = ft_strdup(args[0]);
	split_args = ft_split(args[0], '/');
	while(split_args[i + 1])
	i++;
	pipex->cmd2_args = ft_split(cmd, ' ');
	free(pipex->cmd2_args[0]);
	pipex->cmd2_args[0] = ft_strdup(split_args[i]);
	free_array(split_args);
	if (args[1])
	{
		pipex->cmd2_args[1] = ft_strdup(args[1]);
	}
	free_array(args);
}
