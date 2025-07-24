/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/24 19:08:46 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;

	ppx = malloc(sizeof(t_pipex));
	if (!ppx)
		return (perror("Failed to create struct t_pipex"), 1);
	ft_init(ppx, argc, argv, envp);
	// int	**pipefd;
	// int	*pid;

	// pipefd = ft_makepipe(argc);
	// pid = ft_makepid(argc, pipefd, argc - 4);
	// ft_connect(pid, pipefd, argc - 4);
	// ft_cleanpipe(pipefd, argc - 4);
	// ft_wait(pid);
}

ft_init(t_pipex *ppx, int argc, char **argv, char **envp)
{
	ppx->argc = argc;
	ppx->argv = argv;
	ppx->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ppx->firstcmd = 3;
		ppx->pipenum = argc - 5;
	}
	else
	{
		ppx->firstcmd = 2;
		ppx->pipenum = argc - 4;
	}
	ft_makepipe(ppx);
	ft_makepid(ppx);
}

void	ft_makepipe(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->pipenum)
	{
		if (pipe(ppx->pipefd[i][2]) == -1)
		{
			perror("Pipe failed");
			ft_cleanpipe(ppx, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_makepid(t_pipex *ppx)
{
	int	i;

	i = 0;
	/*alocate the int *ppx->pid
	check if here_doc
	fork*/
}
// int	**ft_makepipe(int argc)
// {
// 	int	i;
// 	int	**pipefd;

// 	i = 0;
// 	while (i < argc - 4)
// 	{
// 		if (pipe(pipefd[i][2] == -1))
// 		{
// 			perror("Pipe failed");
// 			ft_cleanpipe(pipefd, i);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	return (pipefd);
// }

// int	*ft_makepid(int argc, int **pipefd, int size)
// {
// 	int	i;
// 	int	*pid;

// 	i = 0;
// 	while (i < argc - 3)
// 	{
// 		pid[i] = fork;
// 		if (pid[i] == -1)
// 		{
// 			perror("Fork failed");
// 			ft_cleanpipe(pipefd, size);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	return (pid);
// }

void	ft_connect(int *pid, int **pipefd, int size)
{
	int	i;

	ft_firstchild()
	i = 0;
	while (i < size)
	{
		
	}
}
