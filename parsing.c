/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:57:29 by raaga             #+#    #+#             */
/*   Updated: 2022/02/24 18:59:01 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
	{
		i++;
	}
	return (envp[i]);
}

int	check_arg(int argc, char **argv, char **envp, t_pipex *pipex)
{
	char	*s;

	if (argc != 5)
		return (msg_err(ERR_ARG));
	if (*envp == NULL)
		return (0);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
	}
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (pipex->outfile < 0)
	{
		ft_printf("bash: %s: %s\n", argv[4], strerror(errno));
	}
	s = ft_strjoin(find_path(envp), ":");
	pipex->path = complet_path(ft_split(s, ':'));
	free(s);
	pipe(pipex->pipefd);
	return (1);
}

char	**complet_path(char **split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split[i])
	{
		tmp = split[i];
		split[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	split[i] = ft_strjoin(split[i], "");
	return (split);
}
