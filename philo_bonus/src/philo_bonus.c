/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:25:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	one_phylo(t_phylos *setup)
{
	printf("%ld %d is thinking\n", get_time() - setup->start_time, 1);
	printf("%ld %d has taken a fork\n", get_time() - setup->start_time, 1);
	while ((get_time() - setup->start_time) != setup->tt_die)
		usleep(1);
	printf("%ld %d died\n", get_time() - setup->start_time, 1);
	sem_close(setup->print);
	sem_unlink("/PRINT");
	sem_close(setup->forks);
	sem_unlink("/FORKS");
	free(setup);
	return (0);
}

void	routine_controler(t_phylos *phylo)
{
	is_thinking(phylo);
	while (phylo->times_eated < phylo->max_eat)
	{
		taken_fork(phylo);
		is_eating(phylo);
		is_sleeping(phylo);
		is_thinking(phylo);
		if (is_dead(phylo))
		{
			is_died(phylo);
			sem_close (phylo->forks);
			sem_close (phylo->print);
			free(phylo);
			exit(1);
		}
	}
	sem_close (phylo->forks);
	sem_close (phylo->print);
	free(phylo);
	exit(0);
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

int	main(int argc, char *argv[])
{
	t_phylos	*phylo;
	pid_t		*child_pids;

	if (argc < 5 || argc > 6)
		return (usage_message());
	phylo = init_info((const char **)&argv[1]);
	if (!phylo)
		return (error_message());
	if (phylo->no_phylos < 2)
		return (one_phylo(phylo));
	child_pids = init_processes(phylo);
	wait_processes(child_pids, phylo->no_phylos);
	sem_close(phylo->print);
	sem_unlink("/PRINT");
	sem_close(phylo->forks);
	sem_unlink("/FORKS");
	free(phylo);
	free(child_pids);
	return (0);
}
