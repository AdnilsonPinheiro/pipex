/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/08 16:25:15 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_path(char *cmd, char **envp);
static void	ft_free(char **str);
static char	*ft_str2join(char *path, char *str1, char *str2);

void	ft_execute(char *argv, char **envp, int *pipefd)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_errclose(pipefd, "Split failed in ft_execute\n");
	path = ft_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		ft_close(pipefd[0], pipefd[1]);
		ft_putstr_fd("Failed to find command\n", 2);
		return ;
	}
	execve(path, cmd, envp);
	ft_free(cmd);
	free(path);
	path = NULL;
	ft_errclose(pipefd, "execve failed\n");
}

static char	*ft_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (ft_putstr_fd("PATH not found\n", 2), NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i++])
	{
		path_cmd = ft_str2join(path[i], "/", cmd);
		if (!path_cmd)
			return (ft_free(path), NULL);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (ft_free(path), path_cmd);
		free(path_cmd);
	}
	ft_free(path);
	return (NULL);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

static char	*ft_str2join(char *path, char *str1, char *str2)
{
	char	*temp;
	char	*dest;

	if (!path || !str1 || !str2)
		return (NULL);
	temp = ft_strjoin(path, str1);
	if (!temp)
		return (NULL);
	dest = ft_strjoin(temp, str2);
	if (!dest)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	free(temp);
	temp = NULL;
	return (dest);
}
