/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:05:26 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/23 18:54:32 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child(char **argv, char **envp, int *pipefd);
static void	ft_parent(char **argv, char **envp, int *pipefd);

int	main(int argc, char **argv, char **envp)
{
	int		*pipefd[2];
	int		i;
	pid_t	childpid[argc - 3];

	if (argc == 5)
	{
		i = 0;
		while(i < argc - 3)
		{
			if(pipe(pipefd[i]) == -1)
				ft_errclose(pipefd, i - 1, "Pipe failed");
			i++;
		}
		i = 0;
		while (i < argc - 3)
		{
			childpid[i] = fork();
			if (childpid[i] == -1)
					ft_errclose(pipefd, argc - 3, "Fork failed");
			i++;
		}
		i = 0;
		while (childpid[i])
		{
			if (childpid[i] == 0)
				ft_child(argv, envp, pipefd[i]);
			i++;
		}
		// if (pipe(pipefd) == -1)
		// {
		// 	perror("pipe failed");
		// 	exit(EXIT_FAILURE);
		// }
		// childpid = fork();
		// if (childpid == -1)
		// 	ft_errclose(pipefd, "Fork failed");
		// if (childpid == 0)
		// 	ft_child(argv, envp, pipefd);
		// ft_parent(argv, envp, pipefd);
		// close(pipefd[0]);
		// close(pipefd[1]);
		// return (0);
	}
	else
		ft_putstr_fd("Unvalid Format\n./pipex infile cmd1 cmd2 outfile\n", 2);
	return (1);
}

static void	ft_child(char **argv, char **envp, int *pipefd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		ft_errclose(pipefd, "Failed to open infile");
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_errclose(pipefd, "Failed to duplicate pipefd[1]");
	close(pipefd[1]);
	if ((dup2(fd_in, STDIN_FILENO)) == -1)
		ft_errclose(pipefd, "Failed to duplicate infile's fd");
	close(fd_in);
	ft_execute(argv[2], envp, pipefd);
	exit(EXIT_FAILURE);
}

static void	ft_parent(char **argv, char **envp, int *pipefd)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_errclose(pipefd, "Failed to open or create outfile");
	close(pipefd[1]);
	if ((dup2(fd_out, STDOUT_FILENO)) == -1)
		ft_errclose(pipefd, "Failed to duplicate outfile's fd");
	close(fd_out);
	if ((dup2(pipefd[0], STDIN_FILENO)) == -1)
		ft_errclose(pipefd, "Failed to duplicate pipefd[0] to stdin");
	close(pipefd[0]);
	ft_execute(argv[3], envp, pipefd);
}
