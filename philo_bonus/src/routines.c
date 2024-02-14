/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:06:21 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	is_eating(t_philos *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is eating\n", get_timestamp(philo), philo->no);
	sem_post(philo->print);
	philo->eat_time = get_time();
	philo->times_eated++;
	usleep(philo->tt_eat * 1000);
	sem_post(philo->forks);
}

void	is_sleeping(t_philos *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is sleeping\n", get_timestamp(philo), philo->no);
	sem_post(philo->print);
	usleep(philo->tt_sleep * 1000);
}

void	is_thinking(t_philos *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is thinking\n", get_timestamp(philo), philo->no);
	sem_post(philo->print);
}

void	taken_fork(t_philos *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->no);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->no);
	sem_post(philo->print);
}

void	is_died(t_philos *philo)
{
	sem_wait(philo->print);
	printf("%ld %d died\n", get_timestamp(philo), philo->no);
}
