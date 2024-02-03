/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:48:32 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 06:55:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

void	*pylo_routine(void *ptr)
{
	return (ptr);
}

int	wait_process(t_phylos **phylos)
{
	uint32_t	i;
	int32_t		status;

	i = 0;
	while (phylos[i])
		if (!waitpid(phylos[i]->pid, &status, 0))
			return (1);
	return (0);
}

int	init_process(t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	while (phylos[i])
	{
		phylos[i]->sem = sem_open(SEMA_NAME, O_CREAT | O_EXCL);
		if (phylos[i]->pid == 0)
			routine_controler(phylos[i]);
		i++;
	}
	return (0);
}

