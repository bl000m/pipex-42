/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:54:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 11:22:18 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	parsing_environment(t_pipe *data, char *envp[])
{
	data->path = searching_path(envp);
	if (!data->path)
		error_manager(4, data);
	else
		data->path_dir = ft_split(data->path, ':');
}

char	*searching_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] != NULL)
		return (envp[i] + 5);
	else
		return (NULL);
}

char	*find_dir_command(t_pipe *data)
{
	int		i;
	char	*path_dir;
	char	*path_with_command;

	i = 0;
	while (data->path_dir[i])
	{
		path_dir = ft_strjoin(data->path_dir[i], "/");
		path_with_command = ft_strjoin(path_dir, data->commands[0]);
		if (access(data->commands[0], F_OK | X_OK) == 0)
			return (data->commands[0]);
		else if (access(path_with_command, F_OK | X_OK) == 0)
			return (path_with_command);
		free(path_with_command);
		free(path_dir);
		i++;
	}
	return (NULL);
}

void	matching_commands_with_right_path(t_pipe *data, char *argv[], int pos)
{
	data->commands = ft_split(argv[pos], ' ');
	data->dir_command = find_dir_command(data);
	if (!data->dir_command)
		error_manager(3, data);
}
