/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/08 16:33:55 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static pid_t	ft_process(char *argv, char **envp);
static void	ft_invalidargs(char *str);

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	i;
	pid_t	*pids;
	int	pid_count;
	int	j;

	pid_count = 0;
	if (argc < 5)
		ft_invalidargs("Error! Try ./pipex infile cmd1...cmdN outfile");
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_here(argv);
		fd[0] = ft_open("/tmp/here_doc", 0);/*fd init passing & of fd and & of i?*/
		i = 3;
		pids = malloc(sizeof(pid_t) * (argc - 4));
		if (!pids)
			ft_errclose(fd, "pids failed\n");
	}
	else
	{
		fd[0] = ft_open(argv[1], 0);
		i = 2;
		pids = malloc(sizeof(pid_t) * (argc - 3));
		if (!pids)
			ft_errclose(fd, "pids failed\n");
	}
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	while (i < argc - 2)
		pids[pid_count++] = ft_process(argv[i++], envp);
	pids[pid_count++] = fork();
	if (pids[pid_count - 1] == 0)
	{
		fd[1] = ft_open(argv[argc - 1], 1);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execute(argv[argc - 2], envp, NULL);
	}
	j = -1;
	while (++j < pid_count)
		waitpid(pids[j], NULL, 0);
	unlink("/tmp/here_doc");
	free (pids);
}

static pid_t	ft_process(char *argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if ((pipe(pipefd)) == -1)
		perror("Failed to pipe in ft_process");
	pid = fork();
	if (pid == -1)
		ft_errclose(pipefd, "Failed to fork in ft_process");
	if (pid == 0)
	{
		if ((dup2(pipefd[1], STDOUT_FILENO)) == -1)
			perror("dup2 failed in ft_process parent");
		ft_close(pipefd[0], pipefd[1]);
		ft_execute(argv, envp, pipefd);
	}
	else
	{
		if ((dup2(pipefd[0], STDIN_FILENO)) == -1)
			perror("dup2 failed in ft_process child");
		ft_close(pipefd[0], pipefd[1]);
	}
	return (pid);
}

static void	ft_invalidargs(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
