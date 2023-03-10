/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:55:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 15:19:58 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_error(int argc)
{
	if (argc != 5)
	{
		ft_printf("n. of argument incorrected\n");
		exit(1);
	}
}

void	error_manager(int error, t_pipe *data)
{
	if (error == 1)
		ft_printf("ERROR CREATING PIPE: %s\n", strerror(errno));
	else if (error == 2)
		ft_printf("ERROR CREATING SENDING PROCESS: %s\n", strerror(errno));
	else if (error == 3)
		ft_printf("command not found: %s. %s\n",
			data->commands[0], strerror(errno));
	else if (error == 4)
		ft_printf("ENV PATH not set: %s\n", strerror(errno));
	else if (error == 6)
	{
		if (data->file_in)
			close(data->file_in);
		ft_printf("OUTPUT ERROR: %s\n", strerror(errno));
	}
	else if (error == 7)
		ft_printf("ERROR CREATING RECEIVING PROCESS: %s\n", strerror(errno));
	exit_clean(data);
	exit(1);
}
