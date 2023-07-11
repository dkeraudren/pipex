/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:58:38 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/11 19:25:08 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;

	if (argc < 5)
	{
		ft_error("usage: ./pipex_bonus file1 cmd1 cmd2 file2");
		ft_error("or");
		ft_error("./pipex_bonus here_doc <delimiter> cmd1 cmd2 file2");
		return (1);
	}
	pipex = ft_init_pipex();
	if (!pipex)
		return (ft_error("pipex init failed"));
	if (!ft_parsex(pipex, argc, argv, envp))
		return (ft_error("pipex parse failed"));
	status = ft_pipex(pipex);
	if (status == -1)
		return (ft_error("pipex failed"));
	if (pipex->here_doc)
		unlink(pipex->file_in);
	ft_free_pipex(pipex);
	return (status);
}
