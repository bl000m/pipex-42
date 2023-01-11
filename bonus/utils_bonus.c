/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:38:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/10 17:01:51 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	switching_input_output(t_pipe *data, char c)
{
	if (c == 's')
	{
		dup2(data->pipe[1], STDOUT_FILENO);
		dup2(data->file_in, STDIN_FILENO);
	}
	if (c == 'r')
	{
		dup2(data->pipe[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
	}
}

void	executing_command(t_pipe *data, char *envp[], char *argv[])
{
	if (execve(data->dir_command, data->commands, envp) == -1)
		error_manager(3, argv, data);
}

void	creating_pipe(t_pipe *data, char *argv[])
{
	if (pipe(data->pipe) == -1)
		error_manager(1, argv, data);
}

void	creating_sending_child(char *argv[], t_pipe *data, int err)
{
	data->sending_child = fork();
	if (data->sending_child == -1)
		error_manager(err, argv, data);
}

void	creating_receiving_child(char *argv[], t_pipe *data, int err)
{
	data->receiving_child = fork();
	if (data->receiving_child == -1)
		error_manager(err, argv, data);
}