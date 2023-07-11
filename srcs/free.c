/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 21:31:55 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/10 19:36:03 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

void	ft_free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd[i + 1] && pipex->here_doc)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	i = 0;
	while (pipex->cmd[i])
	{
		ft_free_char_array(pipex->cmd[i]);
		i++;
	}
	free(pipex->cmd[i]);
	free(pipex->cmd);
	if (pipex->here_doc)
		free(pipex->limiter);
	else
		free(pipex->file_in);
	free(pipex->file_out);
	free(pipex);
}
