/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:48:32 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:06:21 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	kill_child(int *pids, uint32_t phy_no, pid_t pid)
{
	uint32_t	i;

	i = 0;
	while (phy_no > i)
	{
		if (pids[i] != pid)
			kill(pids[i], 9);
		i++;
	}
}

int	wait_processes(int *pids, uint32_t phy_no)
{
	uint32_t	i;
	pid_t		pid;
	int32_t		status;

	i = 0;
	pid = waitpid(-1, &status, 0);
	if (status)
		kill_child(pids, phy_no, pid);
	else
	{
		while (i < phy_no)
		{
			if (pids[i] != pid)
				waitpid(pids[i], NULL, 0);
			i++;
		}
	}
	return (0);
}

pid_t	*init_processes(t_philos *philo)
{
	uint32_t	i;
	pid_t		*pids;

	i = 0;
	pids = (int *)malloc(sizeof(int) * philo->no_philos);
	while (i < philo->no_philos)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			philo->no = (i + 1);
			free(pids);
			routine_controler(philo);
		}
		else
			pids[i] = philo->pid;
		i++;
	}
	return (pids);
}
