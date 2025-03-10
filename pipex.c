/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/07 18:15:39 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	return (0);
}

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	int		infile_fd;
	int		outfile_fd;
}			t_pipex;

// Créer le pipe
pipe(pipefd);

// Premier fork
pid1 = fork();
if (pid1 == 0)
{
	// Code du premier enfant
	// ...
	// fermer tout les pipes
	exit(0);  // L'enfant1 se termine ici 
}

// Second fork
pid2 = fork();
if (pid2 == 0)
{
	// Code du second enfant
	// ...
	// fermer tout les pipes
	exit(0);
}

// Maintenant que les deux enfants sont créés, le parent peut fermer le pipe
close(pipefd[0]);
close(pipefd[1]);

// Attendre les enfants
waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);

void debug_print_pipex(t_pipex *pipex)
{
    printf("---- Pipex Debug Info ----\n");
    printf("infile: %s\n", pipex->infile);
    printf("outfile: %s\n", pipex->outfile);
    printf("cmd1: %s\n", pipex->cmd1_args[0]);
    printf("cmd1_path: %s\n", pipex->cmd1_path ? pipex->cmd1_path : "NULL");
    printf("cmd2: %s\n", pipex->cmd2_args[0]);
    printf("cmd2_path: %s\n", pipex->cmd2_path ? pipex->cmd2_path : "NULL");
    printf("pipe_fd: [%d, %d]\n", pipex->pipe_fd[0], pipex->pipe_fd[1]);
    printf("pid1: %d, pid2: %d\n", pipex->pid1, pipex->pid2);
    printf("-------------------------\n");
}