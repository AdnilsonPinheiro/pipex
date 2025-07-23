/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errclose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:57:35 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/22 15:58:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_errclose(int **pipefd, int last, char *str)
{
	int	i;

	i = 0;
	while (i <= last)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	perror(str);
	exit(EXIT_FAILURE);
}
