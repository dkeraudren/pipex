/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:30:38 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/10 19:34:58 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	ft_pipex(t_pipex *pipex)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (ft_error("pipe failed"));
	pid = fork();
	if (pid == -1)
		return (ft_error("fork failed"));
	if (pid == 0)
		status = ft_infile(pipex, fd, pipex->cmd[0]);
	else
		status = ft_outfile(pipex, fd, pipex->cmd[1]);
	wait(NULL);
	return (status);
}
