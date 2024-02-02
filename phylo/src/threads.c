/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:48:32 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 21:10:26 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

void	*pylo_routine(void *ptr)
{
	return (ptr);
}

int	join_threads(t_phylos **phylos)
{
	uint32_t i;

	i = 0;
	while (phylos[i])
		if (pthread_join(phylos[i++]->thread, NULL))
			return (1);
	return (0);
}

int	init_thread(t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	while (phylos[i])
	{
		if (pthread_create(&(phylos[i]->thread), NULL, &routine_controler, phylos[i]))
			return (1); //dela
		i++;
	}
	return (0);
}

