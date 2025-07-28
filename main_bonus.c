/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:17:50 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/28 20:38:39 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *arg, int flag);
static void	ft_process(char *arg, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (argc < 6)
		ft_putstr_fd("Invalid input.\n./pipex_bonus infile cmd1 ... cmdN outfile", 2);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		/*here_doc*/
	}
	else
	{
		fd_in = ft_open(argv[1], 1);
		fd_out = ft_open(argv[argc - 1], 2);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		i = 2;
		while (i < argc - 2)
			ft_process(argv[i++], envp);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		ft_execute(argv[argc - 2], envp, NULL);
	}
}

static int	ft_open(char *arg, int flag)
{
	int	res;

	if (flag == 1)
		res = open(arg, O_RDONLY, 0644);
	if (flag == 2)
		res = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (res == -1)
	{
		perror("Failure at ft_open");
		exit(EXIT_FAILURE);
	}
	return (res);
}

static void	ft_process(char *arg, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		perror("Pipe failed");
	pid = fork();
	if (pid == -1)
		perror("Fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_execute(arg, envp, pipefd);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

/*
static void	ft_init(t_pipex *ppx, int argc, char **argv, char **envp);
static void	ft_makepipe(t_pipex *ppx);
static void	ft_makepid(t_pipex *ppx);
static void	ft_connect(t_pipex *ppx, int position);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;

	ppx = malloc(sizeof(t_pipex));
	if (!ppx)
		return (perror("Failed to create struct t_pipex"), 1);
	ft_init(ppx, argc, argv, envp);
	
	
}

static void	ft_init(t_pipex *ppx, int argc, char **argv, char **envp)
{
	ppx->argc = argc;
	ppx->argv = argv;
	ppx->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ppx->firstcmd = 3;
		ppx->pipenum = argc - 5;
	}
	else
	{
		ppx->firstcmd = 2;
		ppx->pipenum = argc - 4;
	}
	ft_makepipe(ppx);
	ft_makepid(ppx);
}

static void	ft_makepipe(t_pipex *ppx)
{
	int	i;

	i = 0;
	(ppx->pipefd) = malloc(sizeof(int *) * ppx->pipenum);
	if (!ppx->pipefd)
		perror("Failed to allocate for ppx->pipefd");
	while (i < ppx->pipenum)
	{
		ppx->pipefd[i] = malloc(sizeof(int) * 2);
		if (!ppx->pipefd[i])
		{
			perror("Failed to allocate memory for pipefd[i]");
			ft_cleanpipe(ppx, i);
			exit(EXIT_FAILURE);
		}
		if (pipe(ppx->pipefd[i]) == -1)
		{
			perror("Pipe failed");
			ft_cleanpipe(ppx, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	ft_makepid(t_pipex *ppx)
{
	int	i;

	ppx->pid = malloc(sizeof(pid_t) * (ppx->pipenum + 1));
	if (!ppx->pid)
	{
		perror("Memory allocation failed for ppx->pid");
		ft_cleanpipe(ppx, ppx->pipenum);
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < ppx->pipenum + 1)
	{
		if ((ppx->pid[i] = fork()) == -1)
		{
			perror("Failed at fork");
			free(ppx->pid);
			ppx->pid = NULL;
			ft_cleanpipe(ppx, ppx->pipenum);
			exit(EXIT_FAILURE);
		}
		if (ppx->pid[i] == 0)
			ft_connect(ppx, i);
		i++;
	}
}

static void	ft_connect(t_pipex *ppx, int position)
{
	int	in_fd;
	int	out_fd;
	int	i;

	i = ppx->firstcmd;
	while (i < ppx->argc - 1)
	{
		if (position == 0)
		{
			in_fd = open(ppx->argv[ppx->argc - 1], O_RDONLY, 0644);
			if (in_fd < 0)
				perror ("Failed open argv[1]");
			close(ppx->pipefd[0][0]);
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
			dup2(ppx->pipefd[0][1], STDOUT_FILENO);
		}
		if (position > 0 && position < ppx->argc - 2)
		{
			dup2(ppx->pipefd[position][0], STDIN_FILENO);
			dup2(ppx->pipefd[position][1], STDOUT_FILENO);
		}
		if (position == ppx->argc - 2)
		{
			out_fd = open(ppx->argv[ppx->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_fd < 0)
				perror("Failed to create or access outfile");
			close(ppx->pipefd[position][1]);
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		ft_execute(ppx->argv[position + ppx->firstcmd], ppx->envp, ppx->pipefd[position]);
		i++;
	}
}
*/