/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:36:31 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/11 19:06:07 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_infile(t_pipex *pipex, int fd[2], char **argv)
{
	int		fd_in;

	fd_in = open(pipex->file_in, O_RDONLY);
	if (fd_in == -1)
	{
		perror(strerror(errno));
		close(fd[0]);
		close(fd[1]);
		return (errno);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_in);
	return (ft_execvp(argv[0], argv, pipex->env));
}

int	ft_outfile(t_pipex *pipex, int fd[2], char **argv)
{
	int		fd_out;

	fd_out = open(pipex->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(strerror(errno));
		close(fd[0]);
		close(fd[1]);
		return (errno);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_out);
	return (ft_execvp(argv[0], argv, pipex->env));
}

int	ft_middle(t_pipex *pipex, int pipe_in[2], int pipe_out[2], char **argv)
{
	dup2(pipe_in[0], STDIN_FILENO);
	dup2(pipe_out[1], STDOUT_FILENO);
	close(pipe_out[0]);
	close(pipe_in[1]);
	return (ft_execvp(argv[0], argv, pipex->env));
}

int	ft_child(t_pipex *pipex, int **pipes, int i)
{
	if (i == 0)
		return (ft_infile(pipex, pipes[i], pipex->cmd[i]));
	else if (pipex->cmd[i + 1] == NULL)
		return (ft_outfile(pipex, pipes[i - 1], pipex->cmd[i]));
	else
		return (ft_middle(pipex, pipes[i - 1], pipes[i], pipex->cmd[i]));
}

int	ft_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		i;
	int		**pipes;

	i = 0;
	pipes = generate_pipes(pipex);
	pipex->pipes = pipes;
	if (!pipes)
		return (ft_error("malloc failed"));
	if (pipex->here_doc)
	{
		if (!ft_here_doc(pipex, pipes[0]))
			return (0);
	}
	while (pipex->cmd[i])
	{
		pid = fork();
		if (pid == -1)
			return (ft_error("fork failed"));
		if (pid == 0)
			return (ft_child(pipex, pipes, i));
		i++;
	}
	wait(NULL);
	return (0);
}
