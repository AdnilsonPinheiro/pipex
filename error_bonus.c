/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/28 18:00:43 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cleanpipe(t_pipex *ppx, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		close(ppx->pipefd[i][0]);
		close(ppx->pipefd[i][1]);
		i++;
	}
	free(*(ppx->pipefd));
	*(ppx->pipefd) = NULL;
	ppx->pipefd = NULL;
}
void	ft_errclose(int *pipefd, char *str)
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror(str);
	exit(EXIT_FAILURE);
}
