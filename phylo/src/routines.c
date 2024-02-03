/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/02 22:28:52 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

void	is_eating(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		if (pthread_mutex_lock(&(phylo->setup->print)))
			return ;
		printf("%ld %d is eating\n", get_timestamp(phylo), phylo->no);
		pthread_mutex_unlock(&(phylo->setup->print));
		pthread_mutex_lock(&(phylo->mut_eat));
		pthread_mutex_lock(&(phylo->setup->mut_die));
		phylo->eat_time = get_time();
		phylo->times_eated++;
		pthread_mutex_unlock(&(phylo->setup->mut_die));
		pthread_mutex_unlock(&(phylo->mut_eat));
		usleep(phylo->setup->tt_eat * 1000);
	}
}

void	is_sleeping(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		if (pthread_mutex_lock(&(phylo->setup->print)))
			return ;
		printf("%ld %d is sleeping\n", get_timestamp(phylo), phylo->no);
		pthread_mutex_unlock(&(phylo->setup->print));
		usleep(phylo->setup->tt_sleep * 1000);
	}
}

void	is_thinking(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		if (pthread_mutex_lock(&(phylo->setup->print)))
			return ;
		printf("%ld %d is thinking\n", get_timestamp(phylo), phylo->no);
		pthread_mutex_unlock(&(phylo->setup->print));
	}
}

void	taken_fork(t_phylos *phylo)
{
	if (!check_dead(phylo))
	{
		if (pthread_mutex_lock(&(phylo->setup->print)))
			return ;
		printf("%ld %d has taken a fork\n", get_timestamp(phylo), phylo->no);
		pthread_mutex_unlock(&(phylo->setup->print));
	}
}

void	is_died(t_phylos *phylo)
{
	if (pthread_mutex_lock(&(phylo->setup->print)))
		return ;
	printf("%ld %d died\n", get_timestamp(phylo), phylo->no);
	pthread_mutex_unlock(&(phylo->setup->print));
	if (pthread_mutex_lock(&(phylo->setup->mut_die)))
		return ;
	phylo->setup->phylo_dead = true;
	pthread_mutex_unlock(&(phylo->setup->mut_die));
}
