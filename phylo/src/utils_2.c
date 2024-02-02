/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:01 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 21:10:31 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	try_fork_first(t_phylos *phylo)
{
	if (!pthread_mutex_lock(&(phylo->l_fork)))
	{
		taken_fork(phylo);
		if (!pthread_mutex_lock(phylo->r_fork))
		{
			// debug_print(phylo, "right fork - "); //debug
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	else
		is_sleeping(phylo);
	return (0);
}

int	try_fork(t_phylos *phylo)
{
	if (!pthread_mutex_lock(phylo->r_fork))
	{
		// debug_print(phylo, "right fork - "); //debug
		taken_fork(phylo);
		if (!pthread_mutex_lock(&(phylo->l_fork)))
		{
			// debug_print(phylo, "left  fork - "); //debug
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	else
		is_sleeping(phylo);
	return (0);
}
