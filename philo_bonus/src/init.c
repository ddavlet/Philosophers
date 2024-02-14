/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:10 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:06:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check_init(t_philos *s)
{
	if (!s->no_philos
		|| !s->tt_die
		|| !s->tt_eat
		|| !s->tt_sleep
		|| !s->max_eat)
		return (1);
	return (0);
}

t_philos	*init_info(const char **args)
{
	t_philos	*philo;

	philo = (t_philos *)malloc(sizeof(t_philos));
	philo->start_time = get_time();
	philo->no_philos = ft_atol(args[0]);
	philo->tt_die = ft_atol(args[1]);
	philo->tt_eat = ft_atol(args[2]);
	philo->tt_sleep = ft_atol(args[3]);
	philo->eat_time = get_time();
	philo->times_eated = 0;
	if (args[4])
		philo->max_eat = ft_atol(args[4]);
	else
		philo->max_eat = UINT32_MAX;
	if (check_init(philo))
	{
		free(philo);
		return (NULL);
	}
	philo->forks = sem_open("/FORKS", O_CREAT, 0644, philo->no_philos / 2);
	philo->print = sem_open("/PRINT", O_CREAT, 0644, 1);
	return (philo);
}
