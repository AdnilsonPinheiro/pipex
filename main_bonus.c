/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/30 19:17:02 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static void	ft_process(char *argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	int	i;

	if (argc < 5)
		ft_putstr_fd("Error! Try ./pipex infile cmd1...cmdN outfile", 2);
	else if (argc >= 5)
	{
		if ((ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]))) == 0)
		{
			pipefd[1] = ft_open(argv[argc - 1], 2);
			dup2(pipefd[1], STDOUT_FILENO);
			ft_close(pipefd[0], pipefd[1]);
			while (ft_strncmp(get_next_line(0), argv[2], ft_strlen(argv[2])))
				ft_putstr_fd("here_doc>", 1);
			i = 3;
			while (i < argc - 2)
				ft_process(argv[i++], envp);
			ft_execute(argv[argc - 2], envp, pipefd);
		}
		else
		{
			pipefd[0] = ft_open(argv[1], 0);
			dup2(pipefd[0], STDIN_FILENO);
			pipefd[1] = ft_open(argv[argc - 1], 1);
			dup2(pipefd[1], STDOUT_FILENO);
			ft_close(pipefd[0], pipefd[1]);
			i = 2;
			while (i < argc - 2)
				ft_process(argv[i++], envp);
			ft_execute(argv[argc - 2], envp, pipefd);
		}
	}
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
