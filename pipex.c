/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:33 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/17 23:43:26 by mdsiurds         ###   ########.fr       */
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

void child_one_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	open_file_in(name, pipex);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		perror("dup2_stdin_child_one");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2_stdout_child_one");
	close_fd(pipex);
	if (ft_strchr(cmd, '/'))
	{
		exctract_args_address_one(cmd, pipex);
		if (access(pipex->cmd1_path, X_OK) != 0)
		{
			perror(*pipex->cmd1_args);
			free_array(pipex->cmd1_args);
			free(pipex->cmd1_path);
			exit(1);
		}
	}
	if (!pipex->cmd1_path)
		find_cmd1_path(cmd, env, pipex);
	execve(pipex->cmd1_path, pipex->cmd1_args, env);
	perror("execve");
	if (pipex->cmd1_path != pipex->cmd1_args[0])
		free(pipex->cmd1_path);
	free_array(pipex->cmd1_args);
	exit(1);
}

void child_two_do(char *name, char *cmd, t_pipex *pipex, char **env)
{
	open_file_out(name, pipex);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2_stdin_child_two");
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		perror("dup2_stdout_child_two");
	close_fd(pipex);
	if (ft_strchr(cmd, '/'))
	{
		exctract_args_address_two(cmd, pipex);
		if (access(pipex->cmd2_path, X_OK) != 0)
		{
			perror(*pipex->cmd2_args);
			free_array(pipex->cmd2_args);
			free(pipex->cmd2_path);
			exit(1);
		}
	}
	if (!pipex->cmd2_path)
		find_cmd2_path(cmd, env, pipex);
	execve(pipex->cmd2_path, pipex->cmd2_args, env);
	perror("execve");
	if (pipex->cmd2_path != pipex->cmd2_args[0])
		free(pipex->cmd2_path);
	free_array(pipex->cmd2_args);
	exit(1);
}

void find_cmd1_path(char *args1, char **env, t_pipex *pipex)
{
	int i;
	char **paths;
	
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putstr_fd(args1, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		exit(1);
	}
	pipex->cmd1_args = ft_split(args1, ' ');
	join_path_one(paths, pipex);
}

void	find_cmd2_path(char *args2, char **env, t_pipex *pipex)
{
	int i;
	char **paths;
	
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putstr_fd(args2, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		exit(1);
	}
	pipex->cmd2_args = ft_split(args2, ' ');
	join_path_two(paths, pipex);
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
	while (paths[i])
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