/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:05:26 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/12 20:08:24 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_firstchild(char **argv, char **envp, int *pipefd);
static void	ft_sncdchild(char **argv, char **envp, int *pipefd);
static void	ft_invalidargs(char *str);
static int	ft_wait(int *pipefd, int child1, int child2);

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	childpid1;
	pid_t	childpid2;

	if (argc != 5)
		ft_invalidargs("Invalid format\n./pipex infile cmd1 cmd2 outfile\n");
	if ((pipe(pipefd) == -1))
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	childpid1 = fork();
	if (childpid1 == -1)
		ft_errclose(pipefd, "1st fork failed");
	if (childpid1 == 0)
		ft_firstchild(argv, envp, pipefd);
	childpid2 = fork();
	if (childpid2 == -1)
		ft_errclose(pipefd, "2nd fork failed");
	if (childpid2 == 0)
		ft_sncdchild(argv, envp, pipefd);
	ft_wait(pipefd, childpid1, childpid2);
}

static void	ft_firstchild(char **argv, char **envp, int *pipefd)
{
	int	fd_in;

	close(pipefd[0]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		ft_errclose(pipefd, "Failed to open argv[1]");
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		ft_errclose(pipefd, "Failed to dup fd_in to STDIN");
	}
	close(fd_in);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_errclose(pipefd, "Failed to dup pipefd[1] to STDOUT");
	close(pipefd[1]);
	ft_execute(argv[2], envp, pipefd);
}

static void	ft_sncdchild(char **argv, char **envp, int *pipefd)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_errclose(pipefd, "Failed to open or create outfile");
	close(pipefd[1]);
	if ((dup2(fd_out, STDOUT_FILENO)) == -1)
	{
		close(fd_out);
		ft_errclose(pipefd, "Failed to duplicate outfile's fd");
	}
	close(fd_out);
	if ((dup2(pipefd[0], STDIN_FILENO)) == -1)
		ft_errclose(pipefd, "Failed to duplicate pipefd[0] to stdin");
	close(pipefd[0]);
	ft_execute(argv[3], envp, pipefd);
}

static void	ft_invalidargs(char *str)
{
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

static int	ft_wait(int *pipefd, pid_t child1, pid_t child2)
{
	int	status1;
	int	status2;

	status1 = -1;
	status2 = -1;
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status1, 0);
	waitpid(child2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (EXIT_FAILURE);
}
