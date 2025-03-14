/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:38:03 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/14 17:42:30 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void debug_print_pipex(t_pipex *pipex)
{
    int i;
    
    printf("\n===== PIPEX DEBUG INFO =====\n");
    
    // Fichiers
    printf("-- Fichiers --\n");
    printf("infile: %s\n", pipex->infile ? pipex->infile : "NULL");
    printf("infile_fd: %d\n", pipex->infile_fd);
    printf("outfile: %s\n", pipex->outfile ? pipex->outfile : "NULL");
    printf("outfile_fd: %d\n", pipex->outfile_fd);
    
    // Pipe
    printf("\n-- Pipe --\n");
    printf("pipe_fd: [%d, %d] (lecture, écriture)\n", pipex->pipe_fd[0], pipex->pipe_fd[1]);
    
    // Processus
    printf("\n-- Processus --\n");
    printf("pid1: %d\n", pipex->pid1);
    printf("pid2: %d\n", pipex->pid2);
    
    // Commande 1
    printf("\n-- Commande 1 --\n");
    printf("cmd1_path: %s\n", pipex->cmd1_path ? pipex->cmd1_path : "NULL");
    printf("cmd1_args: ");
    if (pipex->cmd1_args)
    {
        i = 0;
        while (pipex->cmd1_args[i])
        {
            printf("[%s] ", pipex->cmd1_args[i]);
            i++;
        }
        printf("\n");
    }
    else
        printf("NULL\n");
    
    // Commande 2
    printf("\n-- Commande 2 --\n");
    printf("cmd2_path: %s\n", pipex->cmd2_path ? pipex->cmd2_path : "NULL");
    printf("cmd2_args: ");
    if (pipex->cmd2_args)
    {
        i = 0;
        while (pipex->cmd2_args[i])
        {
            printf("[%s] ", pipex->cmd2_args[i]);
            i++;
        }
        printf("\n");
    }
    else
        printf("NULL\n");
    
    printf("===========================\n\n");
}
