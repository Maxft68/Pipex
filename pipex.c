/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/14 19:15:07 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void initialize(t_pipex *pipex)
{
	pipex->infile = NULL;
	pipex->infile_fd = -1;
	pipex->outfile = NULL;
	pipex->outfile_fd = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	pipex->pipe_fd[0] = -1;// Descripteurs du pipe [0]=lecture, [1]=écriture
	pipex->pipe_fd[1] = -1;// Descripteurs du pipe [0]=lecture, [1]=écriture
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
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	initialize(&pipex);
	debug_print_pipex(&pipex);
	return (0);
}
void verif_access(t_pipex *pipex)
{
	char *name;
	name = pipex->infile;
	if (access(name, F_OK) == -1)
	{
			perror("infile");
	}
	if (access("infile", R_OK) == -1)
	{
			perror("infile");
	}
	if (access("outfile", F_OK) == -1)
	{
			perror("outfile");
	}
	if (access("outfile", W_OK) == -1)
	{
			perror("outfile");
	}
}
// F_OK = Vérifie si le fichier existe.
// R_OK = Vérifie si le fichier est accessible en lecture.
// W_OK = Vérifie si le fichier est accessible en écriture.
// X_OK = Vérifie si le fichier est exécutable.


// // Créer le pipe
// pipe(pipefd);

// // Premier fork
// pid1 = fork();
// if (pid1 == 0)
// {
// 	// Code du premier enfant
// 	// ...
// 	// fermer tout les pipes
// 	execve(path, args, env);
// 	// Si on arrive ici, c'est que execve a échoué
// 	perror("execve");
// 	exit(127) //EXIT_FAILURE);
// }

// // Second fork
// pid2 = fork();
// if (pid2 == 0)
// {
// 	// Code du second enfant
// 	// ...
// 	// fermer tout les pipes
// 	exit(0);
// }

// // Maintenant que les deux enfants sont créés, le parent peut fermer le pipe
// close(pipefd[0]);
// close(pipefd[1]);

// // Attendre les enfants
// waitpid(pid1, NULL, 0);
// waitpid(pid2, NULL, 0);



// exit(127);
// 0 : succès
// 1 : erreur générale
// 126 : commande trouvée mais non exécutable
// 127 ; command not found
// 130 : programme interrompu par CTRL+C

// pipex.infile_fd = open(pipex.infile, O_RDONLY);
// if (pipex.infile_fd == -1) // Si le fichier dentree nexiste pas 
// {
// 	perror(pipex.infile);  // Affiche l'erreur
// }


// if (pid1 == 0) {
// 	// Ouvrir le fichier d'entrée
// 	infile_fd = open(infile, O_RDONLY);
	
// 	// Configurer les redirections
// 	dup2(infile_fd, STDIN_FILENO);
// 	dup2(pipe_fd[1], STDOUT_FILENO);
	
// 	// Fermer les descripteurs devenus inutiles
// 	close(infile_fd);
// 	close(pipe_fd[0]); // Extrémité de lecture non utilisée
// 	close(pipe_fd[1]); // Déjà dupliqué vers STDOUT_FILENO
	
// 	// Exécuter la commande
// 	execve(...);
// }
// dup2(old_fd, new_fd) fait que new_fd devient une copie de old_fd. Si new_fd était déjà ouvert, il est d'abord fermé.

// lancer une commande simple avec juste infile
// dabord trouver le chemin, le mettre dans acces pour verifier puis execve pour lexecuter

// 1. initialiser la struct avec malloc
// 2. fonction qui construit mes commandes, trouver arguments, et trouver cmd pathconf
// 3. execution processus enfant 1 
// 4. execution precessus enfant 2
// 5. waitpid dans le processus parent les 2 enfants 

// Premier enfant (cmd1):                  Second enfant (cmd2):
// +-------------------+                   +-------------------+
// |                   |                   |                   |
// | stdin <- infile   |                   | stdin <- pipe[0]  |
// | stdout -> pipe[1] |                   | stdout -> outfile |
// |                   |                   |                   |
// +-------------------+                   +-------------------+
// 	 |                                        ^
// 	 |                                        |
// 	 +----------------------------------------+
// 			flux de données via le pipe
// infile -> premier enfant -> pipe[1] (écriture) -> pipe[0] (lecture) -> deuxième enfant -> outfile

// dup2(pipex.infile_fd, STDIN_FILENO) fait que l'entrée standard (stdin, fd 0) devient une copie du fichier d'entrée.
// dup2(pipex.pipe_fd[1], STDOUT_FILENO) fait que la sortie standard (stdout, fd 1) devient une copie de l'extrémité d'écriture du pipe.






