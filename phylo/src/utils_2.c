/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:01 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/04 19:10:56 by ddavlety         ###   ########.fr       */
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
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	return (0);
}

int	try_fork(t_phylos *phylo)
{
	if (!pthread_mutex_lock(phylo->r_fork))
	{
		taken_fork(phylo);
		if (!pthread_mutex_lock(&(phylo->l_fork)))
		{
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	return (0);
}

int	usage_message(void)
{
	printf("Error: wrong number of arguments.\nUsage: ./phylosopher"
		"number_of_philosophers time_to_die time_to_eat time_to_sleep"
		"[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	error_message(void)
{
	printf("Error: failed to initialize setup\n");
	return (1);
}
