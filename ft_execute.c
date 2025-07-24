/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:43 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/24 15:29:50 by adpinhei         ###   ########.fr       */
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

	printf("ft_execute here\n");
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_errclose(pipefd, "Split failed in ft_execute");
	path = ft_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		ft_errclose(pipefd, "Failed to find path");
	}
	execve(path, cmd, envp);
	ft_free(cmd);
	free(path);
	path = NULL;
	ft_errclose(pipefd, "execve failed");
}

static char	*ft_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	printf("ft_path here\n");
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_str2join(path[i], "/", cmd);
		if (!path_cmd)
			perror("path_cmd");
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	ft_free(path);
	return (NULL);
}

static void	ft_free(char **str)
{
	int	i;

	printf("ft_free here\n");
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

	printf("ft_str2join here \n");
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
