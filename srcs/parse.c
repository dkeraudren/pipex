/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:57:33 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/06 21:49:26 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char **envp, char *name)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (envp[i])
	{
		while (envp[i][j] == name[j])
			j++;
		if (envp[i][j] == '=')
		{
			tmp = ft_strdup(envp[i] + j + 1);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

t_pipex	*ft_parse_here_doc(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	int		j;

	i = 3;
	j = 0;
	pipex->cmd = (char ***)malloc(sizeof(char **) * ((argc - 4) + 1));
	if (!pipex->cmd)
		return (NULL);
	while (i < argc - 1)
	{
		pipex->cmd[j] = ft_split(argv[i], ' ');
		if (!pipex->cmd[j])
			return (NULL);
		i++;
		j++;
	}
	pipex->cmd[j] = NULL;
	pipex->here_doc = 1;
	pipex->file_in = ".here_doc";
	pipex->limiter = ft_strjoin(argv[2], "\n");
	pipex->file_out = ft_strdup(argv[argc - 1]);
	if (!pipex->file_out)
		return (NULL);
	pipex->env = envp;
	return (pipex);
}

t_pipex	*ft_parsex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_get_max(ft_strlen(argv[1]), 8)) == 0)
		return (ft_parse_here_doc(pipex, argc, argv, envp));
	pipex->cmd = (char ***)malloc(sizeof(char **) * ((argc - 3) + 1));
	if (!pipex->cmd)
		return (NULL);
	while (i < argc - 1)
	{
		pipex->cmd[j] = ft_split(argv[i], ' ');
		if (!pipex->cmd[j])
			return (NULL);
		i++;
		j++;
	}
	pipex->cmd[j] = NULL;
	pipex->file_in = ft_strdup(argv[1]);
	pipex->file_out = ft_strdup(argv[argc - 1]);
	if (!pipex->file_out || !pipex->file_in)
		return (NULL);
	pipex->env = envp;
	return (pipex);
}
