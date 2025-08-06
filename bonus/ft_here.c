/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:23:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/06 15:34:50 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_here(char **argv)
{
	int		tmp;
	char	*input;
	char	*eof;

	tmp = ft_open("/tmp/here_doc", 2);
	if (tmp == -1)
		perror("Failed to create /tmp/here_doc");
	eof = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		input = get_next_line(STDIN_FILENO);
		if ((ft_strncmp(eof, input, ft_strlen(input))) == 0)
			break ;
		ft_putstr_fd(input, tmp);
		free(input);
	}
	free(eof);
	free(input);
	close(tmp);
}
