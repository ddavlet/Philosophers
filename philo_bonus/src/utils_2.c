/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:04:01 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:08:59 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	is_dead(t_philos *philo)
{
	int	time;

	time = philo->tt_die - (get_time() - philo->eat_time);
	if (time <= 0)
	{
		is_died(philo);
		destroy_semaph(philo);
		free(philo);
		exit(1);
	}
}

uint32_t	times_eated(t_philos *philos)
{
	uint32_t	i;

	i = philos->times_eated;
	return (i);
}

void	destroy_semaph(t_philos *philo)
{
	sem_close(philo->print);
	sem_unlink("/PRINT");
	sem_close(philo->forks);
	sem_unlink("/FORKS");
}
