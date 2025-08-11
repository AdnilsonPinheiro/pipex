/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/11 15:09:37 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_open(char *file, int mod)
{
	int	fd;

	if (mod == READ_ONLY)
		fd = open(file, O_RDONLY, 0644);
	if (mod == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mod == APPEND)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Failed at ft_open", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
