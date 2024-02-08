/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:56:45 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:20:16 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	terminate_setup(t_setup **setup_ptr, int code)
{
	t_setup	*setup;

	setup = *setup_ptr;
	pthread_mutex_destroy(&(setup->mut_die));
	pthread_mutex_destroy(&(setup->print));
	free(setup);
	*setup_ptr = NULL;
	return (code);
}

int	terminate_phylos(t_phylos **phylos, int code)
{
	uint32_t	i;

	i = 0;
	if (!phylos)
		return (0);
	while (phylos[i])
	{
		pthread_mutex_destroy(&(phylos[i]->l_fork));
		pthread_mutex_destroy(&(phylos[i]->mut_eat));
		free(phylos[i++]);
	}
	free(phylos);
	return (code);
}
