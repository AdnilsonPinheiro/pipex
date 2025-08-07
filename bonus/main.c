/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/07 18:51:31 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_process(char *argv, char **envp);
static void	ft_invalidargs(char *str);

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (argc < 5)
		ft_invalidargs("Error! Try ./pipex infile cmd1...cmdN outfile");
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_here(argv);
		fd_in = ft_open("/tmp/here_doc", 0);
		i = 3;
	}
	else
	{
		fd_in = ft_open(argv[1], 0);
		i = 2;
	}
	fd_out = ft_open(argv[argc - 1], 1);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_close(fd_in, fd_out);
	while (i < argc - 2)
		ft_process(argv[i++], envp);
	unlink("/tmp/here_doc");
	ft_execute(argv[argc - 2], envp, NULL);
}

static void	ft_process(char *argv, char **envp)
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
		waitpid (pid, NULL, 0);
	}
}

static void	ft_invalidargs(char *str)
{
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}
