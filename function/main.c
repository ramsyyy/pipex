/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:51:20 by raaga             #+#    #+#             */
/*   Updated: 2022/04/11 15:42:48 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_path(char *cmd1, char **split)
{
	char	*tmp;
	char	*cmd;

	tmp = cmd1;
	if (!cmd1)
		return (NULL);
	if (cmd1[0] == '.' || cmd1[0] == '/')
		return (cmd1);
	while (*split)
	{
		cmd = ft_strjoin(*split, tmp);
		if (access(cmd, F_OK) == 0)
		{
			return (cmd);
		}
		free(cmd);
		split++;
	}
	return (NULL);
}

void	ft_son(char **argv, char **envp, t_pipex pipex)
{
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
	{
		err_fd(argv[1]);
		ft_free(pipex.path);
		exit (2);
	}
	pipex.cmd_arg = ft_split(argv[2], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		if (pipex.cmd_arg[0] != NULL)
			err_cmd(pipex.cmd_arg[0]);
		else
			err_cmd("");
		ft_free(pipex.path);
		ft_free(pipex.cmd_arg);
		exit (2);
	}
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	exe(pipex, envp);
}

void	ft_son2(char **argv, char **envp, t_pipex pipex)
{
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (pipex.outfile < 0)
	{
		err_fd(argv[4]);
		ft_free(pipex.path);
		exit (2);
	}
	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		if (pipex.cmd_arg[0] != NULL)
			err_cmd(pipex.cmd_arg[0]);
		else
			err_cmd("");
		ft_free(pipex.path);
		ft_free(pipex.cmd_arg);
		exit (2);
	}
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	exe(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (check_arg(argc, argv, envp, &pipex) == 0)
		return (0);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_son(argv, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_son2(argv, envp, pipex);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free(pipex.path);
	return (0);
}
