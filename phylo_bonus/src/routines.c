/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/06 16:31:12 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

void	is_eating(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		printf("%ld %d is eating\n", get_timestamp(phylo), phylo->no);
		phylo->eat_time = get_time();
		phylo->times_eated++;
		usleep(phylo->setup->tt_eat * 1000);
	}
}

void	is_sleeping(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		printf("%ld %d is sleeping\n", get_timestamp(phylo), phylo->no);
		usleep(phylo->setup->tt_sleep * 1000);
	}
}

void	is_thinking(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		printf("%ld %d is thinking\n", get_timestamp(phylo), phylo->no);
	}
}

void	taken_fork(t_phylos *phylo)
{
	if (!check_dead(phylo))
		printf("%ld %d has taken a fork\n", get_timestamp(phylo), phylo->no);
}

void	is_died(uint32_t j, t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	while (phylos[i])
		if (phylos[i]->no == j)
			break ;
	printf("%ld %d died\n", get_timestamp(phylos[i]), phylos[i]->no);
	phylos[i]->setup->phylo_dead = true;
}
