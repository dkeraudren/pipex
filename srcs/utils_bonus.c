/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:23:53 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/11 20:41:00 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**generate_pipes(t_pipex *pipex)
{
	int	i;
	int	**pipes;

	i = 0;
	while (pipex->cmd[i])
		i++;
	pipes = malloc(sizeof(int *) * (i - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (pipex->cmd[i + 1])
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

int	ft_here_doc(t_pipex *pipex, int fd[2])
{
	int		here_doc;
	char	*line;

	here_doc = open(pipex->file_in, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc == -1)
	{
		perror(strerror(errno));
		close(fd[0]);
		close(fd[1]);
		return (errno);
	}
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, pipex->limiter, ft_strlen(line)) == 0)
		{
			free(line);
			return (1);
		}
		ft_putstr_fd(line, here_doc);
		free(line);
	}
	return (1);
}
