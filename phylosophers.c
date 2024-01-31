/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 20:54:01 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phylosophers.h"

void	debug_print(t_phylos *phylo, const char *txt)
{
	pthread_mutex_lock(&(phylo->setup->print));
	printf("%i: %s", phylo->no, txt);
	pthread_mutex_unlock(&(phylo->setup->print));
}

void	even_routine(t_phylos	*phylo)
{
	if ((phylo->no % 2))
			try_fork_first(phylo);
	else
		try_fork(phylo);
}

void	odd_routine(t_phylos	*phylo)
{
	if ((phylo->no % 2) && phylo->no != phylo->setup->no_phylos)
		try_fork_first(phylo);
	else if (phylo->no != phylo->setup->no_phylos)
		try_fork(phylo);
	else
	{
		usleep(2);
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
	while(phylos[i])
	{
		pthread_mutex_destroy(&(phylos[i]->l_fork));
		pthread_mutex_destroy(&(phylos[i]->mut_eat));
		free(phylos[i++]);
	}
	free(phylos);
}

int	main(int argc, char *argv[])
{
	t_setup		*setup;
	t_phylos	**phylos;
	void		*ptr;

	if (argc < 4)
		return (1);
	setup = init_info((const char **)&argv[1]);
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
