/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:56:12 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 21:10:19 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	is_dead(t_phylos *phylo)
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

uint32_t	times_eated(t_phylos *phylos)
{
	uint32_t	i;

	i = 0;
	pthread_mutex_lock(&(phylos->mut_eat));
	i = phylos->times_eated;
	pthread_mutex_unlock(&(phylos->mut_eat));
	return (i);
}

int	check_dead(t_phylos *phylo)
{
	bool dead;

	pthread_mutex_lock(&(phylo->setup->mut_die));
	dead = phylo->setup->phylo_dead;
	pthread_mutex_unlock(&(phylo->setup->mut_die));
	return (dead);
}

/*Multiplication may overflow*/
void	*check_die(void *ptr)
{
	t_phylos	**phylos;
	uint32_t	i;
	uint32_t	t;

	phylos = ptr;
	while (1)
	{
		i = 0;
		t = 0;
		while (phylos[i])
		{
			if (is_dead(phylos[i]))
				pthread_exit(phylos[i]);
			t += times_eated(phylos[i]);
			if (t == (phylos[i]->setup->max_eat * phylos[i]->setup->no_phylos))
				pthread_exit(NULL);
			i++;
		}
	}
	return (NULL);
}
