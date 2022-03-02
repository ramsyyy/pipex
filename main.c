/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:51:20 by raaga             #+#    #+#             */
/*   Updated: 2022/03/02 20:59:15 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	return (*envp);
}

char	*get_path(char *cmd1, char **split)
{
	char	*tmp;
	char	*cmd;
	
	tmp = ft_strjoin("/", cmd1);
	while (*split)
	{
		cmd = ft_strjoin(*split , tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		split++;
	}
	return (NULL);
}

void	ft_son(char **argv, char **envp, t_pipex pipex)
{
	
	pipex.cmd_arg = ft_split(argv[2], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		ft_printf("%s %s\n", ERR_CMD, pipex.cmd_arg[0]);
		exit(1);
	}
	
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	execve(pipex.cmd, pipex.cmd_arg, envp);
}


void	ft_son2(char **argv, char **envp, t_pipex pipex)
{
	
	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		//dup2(pipex.pipefd[1], 0);
		//dup2(pipex.pipefd[0], 1);
		ft_printf("%s %s\n", ERR_CMD, pipex.cmd_arg[0]);
		exit(1);
	}
	
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	dup2(pipex.outfile, 1);
	
	execve(pipex.cmd, pipex.cmd_arg, envp);
}
int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	
	(void)argv;
	(void)argc;
	if (argc != 5)
		return (msg_err(ERR_ARG));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		return (msg_err(ERR_INFILE));
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (pipex.outfile < 0)
		return (msg_err(ERR_OUTFILE));
	pipex.path = ft_split(find_path(envp), ':');
	pipe(pipex.pipefd);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		ft_son(argv, envp, pipex);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{	
		ft_son2(argv, envp, pipex);
	}
 	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0); 
	//waitpid(pipex.pid2, NULL, 0);

	return (0);
}
