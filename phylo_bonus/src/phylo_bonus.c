/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/07 16:25:17 by ddavlety         ###   ########.fr       */
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
	while (phylo->times_eated < phylo->max_eat)
	{
		sem_wait(phylo->forks);

	}
	free(phylo);
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

int	usage_message(void)
{
	printf("Error: too few arguments.\nUsage: ./phylosopher"
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

	if (argc < 5 || argc > 6)
		return (usage_message());
	phylo = init_info((const char **)&argv[1]);
	if (!phylo)
		return (error_message());
	if (phylo->no_phylos < 2)
		return (one_phylo(phylo));
	init_processes(phylo);
	// phylos = init_phylos(setup); // ??
	terminate_setup(&setup);
	terminate_phylos(phylos);
	return (0);
}
