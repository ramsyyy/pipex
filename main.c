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

char *find_path(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
	{
		i++;
	}
	return (envp[i]);
}

char	*get_path(char *cmd1, char **split)
{
	char	*tmp;
	char	*cmd;
	
	tmp = cmd1;
	if (cmd1[0] == '.' || cmd1[0] == '/')
	{
			return (cmd1);
	}
	while (*split)
	{
		cmd = ft_strjoin(*split , tmp);
		//printf("ASDADS %d\n", access(cmd, F_OK));
		if (access(cmd, F_OK ) == 0)
		{
			
			//printf("ASDADS %d\n", access(cmd, F_OK));
			return (cmd);
		}
		split++;
	}
	return (NULL);	
}

void	ft_son(char **argv, char **envp, t_pipex pipex)
{
	int	res;
	
	pipex.cmd_arg = ft_split(argv[2], ' ');
	//printf("QEQWEQW %d\n", access("/usr/bin//ls", F_OK & X_OK) );
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		printf("%s %s\n", pipex.cmd_arg[0], ERR_CMD);
		exit(1);
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
}
	


void	ft_son2(char **argv, char **envp, t_pipex pipex)
{
	int	res;
	
	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.cmd = get_path(pipex.cmd_arg[0], pipex.path);
	if (pipex.cmd == NULL)
	{
		//res = execve(pipex.cmd, pipex.cmd_arg, envp);
		ft_printf("%s %s\n", pipex.cmd_arg[0], ERR_CMD);
		exit(1);
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
}

char **complet_path(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		split[i] = ft_strjoin(split[i], "/");
		i++;
	}
	split[i] = "";
	return (split);
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
	{
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
		return (0);
	}
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (pipex.outfile < 0)
		return (msg_err(ERR_OUTFILE));
	pipex.path = ft_split(ft_strjoin(find_path(envp), ":"), ':');
	//printf("QWEQWE %s\n",find_path(envp));
	pipex.path = complet_path(pipex.path);
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
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	close(pipex.infile);
	close(pipex.outfile);
 	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0); 
	return (0);
}
