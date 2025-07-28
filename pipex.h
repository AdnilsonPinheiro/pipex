/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:26:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/28 17:37:33 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct t_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		**pipefd;
	pid_t	*pid;
	int		pipenum;
	int		firstcmd;
}t_pipex;


/*mandatory functions*/
void	ft_execute(char *argv, char **envp, int *pipefd);
void	ft_errclose(int *pipefd, char *str);

/*bonus functions*/
void	ft_cleanpipe(t_pipex *ppx, int size);

#endif