/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkeraudr <dkeraudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:55:49 by dkeraudr          #+#    #+#             */
/*   Updated: 2023/07/10 19:09:04 by dkeraudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <../libft/includes/libft.h>

typedef struct s_pipex
{
	char	**env;
	char	***cmd;
	char	*file_in;
	char	*file_out;
	int		**pipes;
	int		here_doc;
	char	*limiter;
}	t_pipex;

// init.c
t_pipex	*ft_init_pipex(void);

// parse.c
t_pipex	*ft_parsex(t_pipex *pipex, int argc, char **argv, char **envp);

// prints.c
void	ft_print_pipex(t_pipex *pipex);
void	ft_print_env(char **env);

// free.c
void	ft_free_pipex(t_pipex *pipex);
void	ft_free_char_array(char **array);

// pipex.c
int		ft_pipex(t_pipex *pipex);
char	*ft_getenv(char **envp, char *name);

// ft_execve.c
int		ft_execvp(char *exe, char **env, char **argv);
#endif