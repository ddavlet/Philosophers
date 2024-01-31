/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 14:21:23 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylosophers.h"

void	is_eating(t_phylos *phylo)
{
	pthread_mutex_lock(&phylo->setup->print);
	printf("%ld %d is eating\n", get_timestamp(phylo), phylo->no);
	pthread_mutex_unlock(&phylo->setup->print);
	pthread_mutex_lock(&(phylo->mut_eat));
	phylo->eat_time = get_time();
	phylo->times_eated++;
	pthread_mutex_unlock(&(phylo->mut_eat));
	usleep(phylo->setup->tt_eat * 1000);
}

void	is_sleeping(t_phylos *phylo)
{
	pthread_mutex_lock(&phylo->setup->print);
	printf("%ld %d is sleeping\n", get_timestamp(phylo), phylo->no);
	pthread_mutex_unlock(&phylo->setup->print);
	usleep(phylo->setup->tt_sleep * 1000);
}

void	is_thinking(t_phylos *phylo)
{
	pthread_mutex_lock(&(phylo->setup->print));
	printf("%ld %d is thinking\n", get_timestamp(phylo), phylo->no);
	pthread_mutex_unlock(&(phylo->setup->print));
}

void	taken_fork(t_phylos *phylo)
{
	pthread_mutex_lock(&phylo->setup->print);
	printf("%ld %d has taken a fork\n", get_timestamp(phylo), phylo->no);
	pthread_mutex_unlock(&phylo->setup->print);
}
