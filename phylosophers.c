/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 16:07:13 by ddavlety         ###   ########.fr       */
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
	while (1)
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
	return (NULL);
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
	{
		debug_print((t_phylos *)ptr, "\n---died----\n");
		is_died((t_phylos *)ptr);
	}
	if (join_threads(phylos))
		return (1);
	return (0);
}
