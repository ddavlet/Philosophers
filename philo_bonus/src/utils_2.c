/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:01 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:25:40 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	is_dead(t_phylos *phylo)
{
	int	time;

	time = phylo->tt_die - (get_time() - phylo->eat_time);
	if (time <= 0)
		return (1);
	else
		return (0);
}

uint32_t	times_eated(t_phylos *phylos)
{
	uint32_t	i;

	i = phylos->times_eated;
	return (i);
}
