/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:51:20 by raaga             #+#    #+#             */
/*   Updated: 2022/03/04 15:00:26 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd1, char **split)
{
	char	*tmp;
	char	*cmd;

	tmp = cmd1;
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
	int	res;

	pipex.cmd_arg = ft_split(argv[2], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		printf("%s %s\n", pipex.cmd_arg[0], ERR_CMD);
		ft_free(pipex.cmd_arg);
		exit (2);
	}
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	close(pipex.outfile);
	res = execve(pipex.cmd, pipex.cmd_arg, envp);
	if (res == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		write(2, pipex.cmd, ft_strlen(pipex.cmd));
		perror(" ");
	}
	ft_free(pipex.cmd_arg);
}

void	ft_son2(char **argv, char **envp, t_pipex pipex)
{
	int	res;

	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		ft_printf("%s %s\n", pipex.cmd_arg[0], ERR_CMD);
		ft_free(pipex.cmd_arg);
		exit (2);
	}
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	dup2(pipex.outfile, 1);
	close(pipex.infile);
	close(pipex.outfile);
	res = execve(pipex.cmd, pipex.cmd_arg, envp);
	if (res == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		write(2, pipex.cmd, ft_strlen(pipex.cmd));
		perror("");
	}
	ft_free(pipex.cmd_arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (check_arg(argc, argv, envp, &pipex) == 0)
		return (0);
	if (pipex.infile >= 0)
	{
		pipex.pid1 = fork();
		if (pipex.pid1 == 0)
			ft_son(argv, envp, pipex);
	}
	if (pipex.outfile >= 0)
	{
		pipex.pid2 = fork();
		if (pipex.pid2 == 0)
			ft_son2(argv, envp, pipex);
	}
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	close(pipex.infile);
	close(pipex.outfile);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free(pipex.path);
	return (0);
}
