/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:25:37 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	is_eating(t_phylos *phylo)
{
	sem_wait(phylo->print);
	printf("%ld %d is eating\n", get_timestamp(phylo), phylo->no);
	sem_post(phylo->print);
	phylo->eat_time = get_time();
	phylo->times_eated++;
	usleep(phylo->tt_eat * 1000);
	sem_post(phylo->forks);
}

void	is_sleeping(t_phylos *phylo)
{
	sem_wait(phylo->print);
	printf("%ld %d is sleeping\n", get_timestamp(phylo), phylo->no);
	sem_post(phylo->print);
	usleep(phylo->tt_sleep * 1000);
}

void	is_thinking(t_phylos *phylo)
{
	sem_wait(phylo->print);
	printf("%ld %d is thinking\n", get_timestamp(phylo), phylo->no);
	sem_post(phylo->print);
}

void	taken_fork(t_phylos *phylo)
{
	sem_wait(phylo->forks);
	sem_wait(phylo->print);
	printf("%ld %d has taken a fork\n", get_timestamp(phylo), phylo->no);
	printf("%ld %d has taken a fork\n", get_timestamp(phylo), phylo->no);
	sem_post(phylo->print);
}

void	is_died(t_phylos *phylo)
{
	sem_wait(phylo->print);
	printf("%ld %d died\n", get_timestamp(phylo), phylo->no);
}
