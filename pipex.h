/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:26:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/06 15:09:04 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

/*mandatory functions*/
void	ft_execute(char *argv, char **envp, int *pipefd);
void	ft_errclose(int *pipefd, char *str);

/*bonus functions*/
void	ft_close(int fd1, int fd2);
int		ft_open(char *file, int mod);
void	ft_here(char **argv);

#endif