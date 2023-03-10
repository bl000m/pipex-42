/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:03:25 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 14:48:11 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closing_input_output(t_pipe *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->file_in);
	close(data->file_out);
}

void	waiting_childs_finishing(t_pipe *data)
{
	waitpid(data->sending_child, NULL, 0);
	waitpid(data->receiving_child, NULL, 0);
}

void	free_path_dir(t_pipe *data)
{
	int	i;

	i = 0;
	if (data->path_dir)
	{
		while (data->path_dir[i])
		{
			free(data->path_dir[i]);
			data->path_dir[i] = NULL;
			i++;
		}
		free(data->path_dir);
		data->path_dir = NULL;
	}
}

void	free_commands(t_pipe *data)
{
	int	i;

	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
		{
			free(data->commands[i]);
			i++;
		}
		free(data->commands);
	}
}

void	exit_clean(t_pipe *data)
{
	free_commands(data);
	free_path_dir(data);
	free(data);
	if (data->pipe[0])
		close(data->pipe[0]);
	if (data->pipe[1])
		close(data->pipe[1]);
	if (data->file_in)
		close(data->file_in);
	if (data->file_out)
		close(data->file_out);
}
