/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/02 22:24:43 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

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
		usleep(10);
		try_fork(phylo);
	}
}

void	odd_routine(t_phylos	*phylo)
{
	if ((phylo->no % 2) && phylo->no != phylo->setup->no_phylos)
		try_fork_first(phylo);
	else if (phylo->no != phylo->setup->no_phylos)
		try_fork(phylo);
	else
	{
		usleep(10);
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

void	terminate_setup(t_setup **setup_ptr)
{
	t_setup	*setup;

	setup = *setup_ptr;
	pthread_mutex_destroy(&(setup->mut_die));
	pthread_mutex_destroy(&(setup->print));
	free(setup);
	*setup_ptr = NULL;
}

void	terminate_phylos(t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	if (!phylos)
		return ;
	while(phylos[i])
	{
		pthread_mutex_destroy(&(phylos[i]->l_fork));
		pthread_mutex_destroy(&(phylos[i]->mut_eat));
		free(phylos[i++]);
	}
	free(phylos);
}

int	usage_message()
{
	printf("Error: too few arguments.\nUsage: ./phylosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_setup		*setup;
	t_phylos	**phylos;
	void		*ptr;

	if (argc < 5 || argc > 6)
		return (usage_message());
	setup = init_info((const char **)&argv[1]);
	if (setup->no_phylos < 2)
		return (one_phylo(setup));
	phylos = init_phylos(setup);
	pthread_create(&(setup->th_die), NULL, &check_die, phylos);
	init_thread(phylos);
	if (pthread_join(setup->th_die, &ptr))
		return (1);
	if (ptr)
		is_died((t_phylos *)ptr);
	else
		;
	if (join_threads(phylos))
		return (1);
	terminate_setup(&setup);
	terminate_phylos(phylos);
	return (0);
}
