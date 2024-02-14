/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:14:32 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	one_philo(t_philos *setup)
{
	printf("%ld %d is thinking\n", get_time() - setup->start_time, 1);
	printf("%ld %d has taken a fork\n", get_time() - setup->start_time, 1);
	while ((get_time() - setup->start_time) != setup->tt_die)
		usleep(1);
	printf("%ld %d died\n", get_time() - setup->start_time, 1);
	destroy_semaph(setup);
	free(setup);
	return (0);
}

void	routine_controler(t_philos *philo)
{
	is_thinking(philo);
	while (philo->times_eated < philo->max_eat)
	{
		usleep(200);
		taken_fork(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		is_dead(philo);
	}
	destroy_semaph(philo);
	free(philo);
	exit(0);
}

int	usage_message(void)
{
	printf("Error: wrong number of arguments.\nUsage: ./philosopher"
		"number_of_philosophers time_to_die time_to_eat time_to_sleep"
		"[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	error_message(void)
{
	printf("Error: failed to initialize setup\n");
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philos	*philo;
	pid_t		*child_pids;

	if (argc < 5 || argc > 6)
		return (usage_message());
	philo = init_info((const char **)&argv[1]);
	if (!philo)
		return (error_message());
	if (philo->no_philos < 2)
		return (one_philo(philo));
	child_pids = init_processes(philo);
	destroy_semaph(philo);
	wait_processes(child_pids, philo->no_philos);
	free(philo);
	free(child_pids);
	return (0);
}
