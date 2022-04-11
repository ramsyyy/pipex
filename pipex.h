/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:50:47 by raaga             #+#    #+#             */
/*   Updated: 2022/04/11 17:07:20 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define ERR_ARG "Invalid number of arguments.\n"
# define ERR_OUTFILE "Invalid outfile.\n"
# define ERR_CMD ":command not found"

typedef struct s_pipex	t_pipex;
struct			s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**path;
	char	**cmd_arg;
	char	*cmd;
};

int		msg_err(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_free(char **split);
int		check_arg(int argc, char **argv, char **envp, t_pipex *pipex);
char	**complet_path(char **split);
void	err_fd(char *s);
void	exe(t_pipex pipex, char **envp);
void	err_cmd(char *s);
int		ft_strlen(const char *str);

#endif