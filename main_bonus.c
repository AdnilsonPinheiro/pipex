/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/24 17:54:08 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	**pipefd;
	int	*pid;

	pipefd = ft_makepipe(argc);
	pid = ft_makepid(argc, argv, envp, pipefd);
	ft_cleanpipe(pipefd, argc - 4);
	ft_wait(pid);
}

int	**ft_makepipe(int argc)
{
	int	i;
	int	**pipefd;

	i = 0;
	while (i < argc - 4)
	{
		if (pipe(pipefd[i][2] == -1))
		{
			perror("Pipe failed");
			ft_cleanpipe(pipefd, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefd);
}
int	*ft_makepid(int argc, char **argv, char **envp, int **pipefd)
{
	int	i;
	int	*pid;

	i = 0;
	while (i < argc - 3)
	{
		pid[i] = fork;
		if (pid[i] == -1)
			perror("Fork failed"); /*clean the pipe*/
		if (pid[i] == 0)
			ft_child(argc, argv[i + 2], envp, pipefd[i]);
		i++;
	}
	return (pid);
}

void	ft_child(int argc, char *argv, char **envp, int *pipefd)
{
	
}
