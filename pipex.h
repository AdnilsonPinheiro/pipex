/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:26:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/12 16:21:05 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

/*Struct for bonus*/
typedef struct t_pipe
{
	pid_t	*pids;
	int		pid_count;
	int		first_cmd;
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**argv;
	char	**envp;
}	t_pipe;

/*ft_open macros*/
enum e_open_flag
{
	READ_ONLY,
	TRUNC,
	APPEND
};

/*mandatory functions*/
void	ft_execute(char *argv, char **envp, int *pipefd);
void	ft_errclose(int *pipefd, char *str);

/*bonus functions*/
void	ft_close(int fd1, int fd2);
int		ft_open(char *file, int mod);
void	ft_here(char **argv);
void	ft_init(t_pipe *ppx, int argc, char **argv, char **envp);
void	ft_wait_bonus(t_pipe *ppx);
void	ft_last(t_pipe *ppx, char *outfile);
void	get_next_line_clear(void);

#endif