/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:50:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/04 14:51:41 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "./ft_printf/ft_printf.h"

# define ERR_ARG "Invalid number of arguments.\n"
# define ERR_INFILE strerror(errno)
# define ERR_OUTFILE "Invalid outfile.\n"
# define ERR_CMD ":command not found"

typedef struct  s_pipex t_pipex;
struct          s_pipex
{
    int infile;
    int outfile;
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    char **path;
    char **cmd_arg;
    char *cmd;
};

int     msg_err(char *str);
int     ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif