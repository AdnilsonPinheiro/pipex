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

void	ft_errclose(int *pipefd, char *str)
{
	if (close(pipefd[0]) == -1)
		perror("Failed to close pipefd[0]");
	if (close(pipefd[1]) == -1)
		perror("Failed to close pipefd[1]");
	perror(str);
	exit(EXIT_FAILURE);
}
