/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:23:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/04 19:25:10 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_process(char *argv, char **envp);

void	ft_here(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		i;
	int		tmp;
	char	*input;
	char	*eof;

	tmp = ft_open("/tmp/here_doc", 2);
	eof = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		input = get_next_line(STDIN_FILENO);
		if ((ft_strncmp(input, eof, ft_strlen(input))) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, tmp);
		free(input);
	}
	free(eof);
	pipe(pipefd);
	pipefd[0] = tmp;
	pipefd[1] = ft_open(argv[argc - 1], 1);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	ft_close(pipefd[0], pipefd[1]);
	i = 3;
	fprintf(stdout, "caiu aqui oh");
	while (i < argc - 2)
		ft_process(argv[i++], envp);
	close(tmp);
	ft_execute(argv[argc - 2], envp, pipefd);
	unlink("/tmp/here_doc");
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
		fprintf(stdout, "caiu aqui oh");
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
