/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 14:18:15 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phylosophers.h"

void	debug_print(t_phylos *phylo, const char *txt)
{
	pthread_mutex_lock(&(phylo->setup->print));
	printf("%i: %s", phylo->no, txt);
	pthread_mutex_unlock(&(phylo->setup->print));
}

int is_dead(t_phylos *phylo)
{
	int	time;
	pthread_mutex_lock(&(phylo->mut_eat));
		time = phylo->setup->tt_die  - (get_time() - phylo->eat_time);
	pthread_mutex_unlock(&(phylo->mut_eat));
	if (time <= 0)
		return (1);
	else
		return (0);
}

time_t	get_timestamp(t_phylos *phylo)
{
	return (get_time() - phylo->setup->start_time);
}

int	try_fork_first(t_phylos *phylo)
{
	if (!pthread_mutex_lock(&(phylo->l_fork)))
	{
		// debug_print(phylo, "left  fork - "); //debug
		taken_fork(phylo);
		if (!pthread_mutex_lock(phylo->r_fork))
		{
			// debug_print(phylo, "right fork - "); //debug
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	else
		is_sleeping(phylo);
	return (0);
}

int	try_fork(t_phylos *phylo)
{
	if (!pthread_mutex_lock(phylo->r_fork))
	{
		// debug_print(phylo, "right fork - "); //debug
		taken_fork(phylo);
		if (!pthread_mutex_lock(&(phylo->l_fork)))
		{
			// debug_print(phylo, "left  fork - "); //debug
			taken_fork(phylo);
			is_eating(phylo);
		}
	}
	else
		is_sleeping(phylo);
	return (0);
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
		usleep(100);
		try_fork(phylo);
	}
}

void	*some_fucntion(void *ptr)
{
	t_phylos	*phylo;

	phylo = (t_phylos *)ptr;
	is_thinking(phylo);
	while ()
	{
		if (!(phylo->setup->no_phylos % 2))
			even_routine(phylo);
		else
			odd_routine(phylo);
		pthread_mutex_unlock(phylo->r_fork);
		pthread_mutex_unlock(&(phylo->l_fork));
		is_sleeping(phylo);
		is_thinking(phylo);
	}
	return (NULL);
}

int	join_threads(t_phylos **phylos)
{
	uint32_t i;

	i = 0;
	while (phylos[i])
		if (pthread_join(phylos[i++]->thread, NULL))
			return (1);
	return (0);
}

int	init_thread(t_phylos **phylos)
{
	uint32_t	i;

	i = 0;
	while (phylos[i])
	{
		if (pthread_create(&(phylos[i]->thread), NULL, &some_fucntion, phylos[i]))
			return (1); //dela
		i++;
	}
	return (0);
}

void	*check_die(void *ptr)
{
	t_phylos	**phylos;
	uint32_t	i;

	phylos = ptr;
	i = 0;
	while (1)
	{
		while (phylos[i])
		{
			if (is_dead(phylos[i]))
				pthread_exit(phylos[i]);
		}
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
		debug_print(ptr, "\n---died----\n");
	if (join_threads(phylos))
		return (1);
	return (0);
}
