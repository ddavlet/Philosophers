/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/06 14:07:44 by ddavlety         ###   ########.fr       */
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

void	*routine_controler(t_phylos *phylo)
{
	is_thinking(phylo);
	while (phylo->times_eated < phylo->setup->max_eat)
	{
		if (!sem_wait(phylo->sem))
		{
			phylo->setup->no_phylos -= 2;
			if (try_fork(phylo))
			{
				taken_fork(phylo);
				taken_fork(phylo);
				is_eating(phylo);
				is_sleeping(phylo);
			}
		}
		// is_thinking(phylo);
	}
	// pthread_exit(phylo);
	return (NULL);
}

void	terminate_setup(t_setup **setup_ptr)
{
	t_setup	*setup;

	setup = *setup_ptr;
	free(setup);
	*setup_ptr = NULL;
}

void	terminate_phylos(t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	if (!phylos)
		return ;
	while (phylos[i])
	{
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
	int			status;

	if (argc < 5 || argc > 6)
		return (usage_message());
	setup = init_info((const char **)&argv[1]);
	if (setup->no_phylos < 2)
		return (one_phylo(setup));
	phylos = init_phylos(setup);
	init_process(phylos);
	setup->child = fork();
	wait_process(phylos);
	if (!setup->child)
		check_die(phylos);
	if (waitpid(setup->child, &status, 0))
		is_died(WIFSIGNALED(status), phylos);
	terminate_setup(&setup);
	terminate_phylos(phylos);
	return (0);
}
