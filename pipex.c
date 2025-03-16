/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/16 17:48:18 by maxoph           ###   ########.fr       */
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
	if (pipe(pipex.pipe_fd) == -1)
		return (perror("pipe"), 1);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_one_do(argv[1], argv[2], &pipex, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_two_do(argv[4], argv[3], &pipex, env);
	debug_print_pipex(&pipex);
	return (0);
}

void child_one_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	open_file_in(name, pipex);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		perror("dup2_stdin_child_one");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2_stdout_child_one");
	close(pipex->infile_fd);
	close(pipex->pipe_fd[0]); // cote lecture du pipe
	close(pipex->pipe_fd[1]); // dup2 l'a mis en stdout
	exctract_args_one(cmd, pipex); //si argv[2] = /bin/ls -la alors cmd1_args[0] = bin/ls et arg[1] = -la 
	find_cmd1_path(pipex->cmd1_args[0], env, pipex);
	
	execve(pipex->cmd1_path, pipex->cmd1_args, env);
	// si on passe ce execve alors execve a fail
	perror("execve");
	if (pipex->cmd1_path != pipex->cmd1_args[0])
		free(pipex->cmd1_path);
	free_array(pipex->cmd1_args);
	exit(1);
}
void find_cmd1_path(char *cmd1, char **env, t_pipex *pipex)
{
	int i;
	i = 0;
	char **paths;
	test_path(cmd1, pipex);
	if (pipex->cmd1_path != NULL) // si le chemin est deja donner alors plus besoin de le chercher
		return;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putstr_fd(cmd1, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		exit(1);
	}
	join_path(paths, pipex);
}

void join_path(char **paths, t_pipex *pipex)
{
	int i;
	i = 0;
	while (paths[i])
	{
		pipex->cmd1_path = ft_strjoin3(paths[i], "/", pipex->cmd1_args[0]);
		if (acces(pipex->cmd1_path, X_OK) == 0)
		{
			free_array(paths);
			return;
		}
		pipex->cmd1_path = NULL;
		i++;
	}
	ft_putstr_fd("Command not found", 2);
	exit(127);
}

void test_path(char *cmd1, t_pipex *pipex)
{
	if (ft_strchr(cmd1, '/'))
	{
		if (acces(cmd1, X_OK) == 0) // reussi
		{
			pipex->cmd1_path = cmd1;
			return ;
		}
		else
		{
			perror("cmd1");
			exit(1);
		}
	}
	return ;
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *s4;
	char *s5;
	
	s4 = ft_strjoin(s1, s2);
	s5 = ft_strjoin(s4, s3);
	
	return(s4);
}


void exctract_args_one(char *cmd, t_pipex *pipex)
{
	pipex->cmd1_args = ft_split(cmd, ' ');
	if (!pipex->cmd1_args || !pipex->cmd1_args[0])
	{
		free_array(pipex->cmd1_args);
		perror("cmd_one");
		exit(1);
	}
}

void  exctract_args_two(char *cmd, t_pipex *pipex)
{
	pipex->cmd2_args = ft_split(cmd, ' ');
	if (!pipex->cmd2_args || !pipex->cmd2_args[0])
	{
		free_array(pipex->cmd2_args);
		perror("cmd_two");
		exit(1);
	}
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


void child_two_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	
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
		exit(1);
	}
}


void check_infile(t_pipex *pipex)
{
	if (access("pipex->infile", F_OK) == -1)
	{
		perror("pipex->infile");
	}
	if (access("pipex->infile", R_OK) == -1)
	{
		perror("pipex->infile");
	}
}

void check_outfile(t_pipex *pipex)
{
	if (access("pipex->outfile", W_OK) == -1)
	{
		perror("pipex->outfile");
		//free_all
		exit(1);
	}
}

// F_OK = Vérifie si le fichier existe.
// R_OK = Vérifie si le fichier est accessible en lecture.
// W_OK = Vérifie si le fichier est accessible en écriture.
// X_OK = Vérifie si le fichier est exécutable.

// Flags de création et comportement (optionnels) :
// O_CREAT : Crée le fichier s'il n'existe pas
// O_EXCL : Utilisé avec O_CREAT, échoue si le fichier existe déjà
// O_TRUNC : Si le fichier existe, le vide (supprime son contenu)
// O_APPEND : Les écritures se font à la fin du fichier
// O_RDONLY : Ouverture en lecture seule
// O_WRONLY : Ouverture en écriture seule
// O_RDWR : Ouverture en lecture et écriture

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






