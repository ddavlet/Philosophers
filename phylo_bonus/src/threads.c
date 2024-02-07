/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:48:32 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/07 16:24:30 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	wait_processes(t_phylos *phylos)
{
	uint32_t	i;
	int32_t		status;

	while (phylos)
		waitpid(phylos->pid, &status, 0);
}

int	init_processes(t_phylos *phylos)
{
	phylos->pid = fork();
	if (phylos->pid == 0)
		routine_controler(phylos);
	else
		return (1);
	return (0);
}

