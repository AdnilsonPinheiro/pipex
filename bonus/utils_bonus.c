/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/06 15:18:30 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_open(char *file, int mod)
{
	int	fd;

	if (mod == 0)
		fd = open(file, O_RDONLY, 0644);
	if (mod == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mod == 2)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("Failed at ft_open");
	return (fd);
}
