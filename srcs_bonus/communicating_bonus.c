/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communicating_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:13:53 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/14 18:30:41 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// parent can't exec otherwise sleep 1 and 1 = 2
void	communicating(t_pipe *data, char *argv[], char *envp[])
{
	while (data->pos <= data->argc - 2)
	{
		ft_printf("data->here_doc = %d\n", data->here_doc);
		creating_pipe(data, argv);
		creating_child(argv, data, 2);
		if (data->child == 0)
			sending_process(data, argv, envp);
		closing_input_output(data);
		data->pos++;
	}
	exit_clean(data, 'p');
	closing_input_output(data);
  close(data->file_in);
	close(data->file_out);
	waitpid(data->child, NULL, WNOHANG);
}

void	sending_process(t_pipe *data, char *argv[], char *envp[])
{
	if (data->file_in < 0)
	{
		closing_input_output(data);
		exit(1);
	}
	if (data->pos == data->argc - 2)
	{
		if (dup2(data->file_out, STDOUT_FILENO) < 0)
			ft_printf("ERROR in switching fd in sending_process\n");
	}
	else
	{
		if (dup2(data->pipe[1], STDOUT_FILENO) < 0)
			ft_printf("ERROR in switching fd in sending_process\n");
	}
	closing_input_output(data);
	matching_commands_with_right_path(data, argv, data->pos);
	executing_command(data, envp, argv);
}
