/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:30:59 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/12 16:21:05 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_init(t_pipe *ppx, int argc, char **argv, char **envp)
{
	ppx->pid_count = 0;
	ppx->argc = argc;
	ppx->argv = argv;
	ppx->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ppx->fd_in = ft_open("/tmp/here_doc", APPEND);
		ppx->first_cmd = 3;
	}
	else
	{
		ppx->fd_in = ft_open(argv[1], READ_ONLY);
		ppx->first_cmd = 2;
	}
	ppx->pids = malloc(sizeof(pid_t) * (argc - ppx->first_cmd + 1));
	if (!ppx->pids)
		ft_putstr_fd("Error! Failed to malloc in ft_init\n", 2);
}

void	ft_wait_bonus(t_pipe *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->pid_count)
	{
		waitpid(ppx->pids[i], NULL, 0);
		i++;
	}
	free(ppx->pids);
	free(ppx);
	unlink("/tmp/here_doc");
}

void	ft_last(t_pipe *ppx, char *outfile)
{
	if (ft_strncmp(ppx->argv[1], "here_doc", ft_strlen(ppx->argv[1])) == 0)
		ppx->fd_out = ft_open(outfile, APPEND);
	else
		ppx->fd_out = ft_open(outfile, TRUNC);
	dup2(ppx->fd_out, STDOUT_FILENO);
	close(ppx->fd_out);
	ft_execute(ppx->argv[ppx->argc - 2], ppx->envp, NULL);
}
