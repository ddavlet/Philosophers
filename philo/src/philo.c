/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:20:34 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_phylo(t_setup *setup)
{
	printf("%ld %d is thinking\n", get_time() - setup->start_time, 1);
	printf("%ld %d has taken a fork\n", get_time() - setup->start_time, 1);
	while ((get_time() - setup->start_time) != setup->tt_die)
		usleep(1);
	printf("%ld %d died\n", get_time() - setup->start_time, 1);
	free(setup);
	return (0);
}

void	even_routine(t_phylos	*phylo)
{
	if ((phylo->no % 2))
		try_fork_first(phylo);
	else
	{
		usleep(200);
		try_fork(phylo);
	}
}

void	odd_routine(t_phylos	*phylo)
{
	if (phylo->no == phylo->setup->no_phylos)
	{
		usleep(400);
		try_fork(phylo);
	}
	else if ((phylo->no % 2))
		try_fork_first(phylo);
	else
	{
		usleep(200);
		try_fork(phylo);
	}
}

void	*routine_controler(void *ptr)
{
	t_phylos	*phylo;

	phylo = (t_phylos *)ptr;
	is_thinking(phylo);
	while (phylo->times_eated < phylo->setup->max_eat)
	{
		if (!(phylo->setup->no_phylos % 2))
			even_routine(phylo);
		else
			odd_routine(phylo);
		pthread_mutex_unlock(phylo->r_fork);
		pthread_mutex_unlock(&(phylo->l_fork));
		is_sleeping(phylo);
		is_thinking(phylo);
		if (check_dead(phylo))
			pthread_exit(NULL);
	}
	pthread_exit(phylo);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_setup		*setup;
	t_phylos	**phylos;
	void		*ptr;

	if (argc < 5 || argc > 6)
		return (usage_message());
	setup = init_info((const char **)&argv[1]);
	if (!setup)
		return (error_message());
	if (setup->no_phylos < 2)
		return (one_phylo(setup));
	phylos = init_phylos(setup);
	if (!phylos)
		return (terminate_setup(&setup, 1));
	pthread_create(&(setup->th_die), NULL, &check_die, phylos);
	init_thread(phylos);
	pthread_join(setup->th_die, &ptr);
	if (ptr)
		is_died((t_phylos *)ptr);
	join_threads(phylos);
	terminate_setup(&setup, 0);
	terminate_phylos(phylos, 0);
	return (0);
}
