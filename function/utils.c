/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:40:56 by raaga             #+#    #+#             */
/*   Updated: 2022/04/11 15:42:38 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	err_cmd(char *s)
{
	write(2, s, ft_strlen(s) + 1);
	write(2, " ", 1);
	write(2, ERR_CMD, ft_strlen(ERR_CMD));
	write(2, "\n", 1);
}

void	err_fd(char *s)
{
	write(2, "bash: ", ft_strlen("bash: "));
	write(2, s, ft_strlen(s));
	write(2, " :", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	exe(t_pipex pipex, char **envp)
{
	int	res;

	res = execve(pipex.cmd, pipex.cmd_arg, envp);
	if (res == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		write(2, pipex.cmd, ft_strlen(pipex.cmd));
		perror(" ");
	}
	ft_free(pipex.cmd_arg);
}
