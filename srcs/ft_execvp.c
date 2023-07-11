/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:35:24 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/11 20:39:23 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "pipex.h"

char	*parse_path(char **splited_path, char *exe)
{
	int		i;
	char	*potential_exe_dir;
	char	*potential_exe_path;

	i = 0;
	while (splited_path[i])
	{
		potential_exe_dir = ft_strjoin(splited_path[i], "/");
		potential_exe_path = ft_strjoin(potential_exe_dir, exe);
		free(potential_exe_dir);
		if (access(potential_exe_path, X_OK) == 0)
		{
			ft_free_char_array(splited_path);
			return (potential_exe_path);
		}
		free(potential_exe_path);
		i++;
	}
	return (NULL);
}

char	*find_exe_path(char *exe, char **env)
{
	char	*path;
	char	**splited_path;
	char	*potential_exe_path;

	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	free(path);
	if (!splited_path)
		return (NULL);
	potential_exe_path = parse_path(splited_path, exe);
	if (potential_exe_path)
		return (potential_exe_path);
	ft_free_char_array(splited_path);
	return (NULL);
}

int	ft_execvp(char *exe, char **argv, char **env)
{
	char	*exe_path;
	int		i;
	int		ret;

	exe_path = NULL;
	i = 0;
	while (exe && exe[i])
	{
		if (exe[i] == '/')
			return (execve(exe, argv, env));
		i++;
	}
	if (exe)
		exe_path = find_exe_path(exe, env);
	if (!exe || !exe_path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(exe, 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
	ret = execve(exe_path, argv, env);
	free(exe_path);
	return (ret);
}
