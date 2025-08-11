/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/11 16:35:23 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static pid_t	ft_process(char *argv, char **envp);
static void		ft_invalidargs(char *str);

int	main(int argc, char **argv, char **envp)
{
	p_struct	*ppx;

	ppx = malloc(sizeof(p_struct));
	if (!ppx)
		return (ft_putstr_fd("Failed to allocate for p_struct *ppx\n", 2), 0);
	if (argc < 5)
		ft_invalidargs("Error! Try ./pipex infile cmd1...cmdN outfile");
	else if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_here(argv);
		ft_init(ppx, argc, argv, envp);
	}
	else
		ft_init(ppx, argc, argv, envp);
	dup2(ppx->fd_in, STDIN_FILENO);
	close (ppx->fd_in);
	while (ppx->first_cmd < argc - 2)
		ppx->pids[ppx->pid_count++] = ft_process(argv[ppx->first_cmd++], envp);
	ppx->pids[ppx->pid_count++] = fork();
	if (ppx->pids[ppx->pid_count - 1] == 0)
		ft_last(ppx, argv[argc - 1]);
	ft_wait_bonus(ppx);
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
