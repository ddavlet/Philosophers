/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:56:12 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 15:57:46 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./phylosophers.h"

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

int	check_dead(t_phylos *phylo)
{
	bool dead;

	pthread_mutex_lock(&(phylo->setup->mut_die));
	dead = phylo->setup->phylo_dead;
	pthread_mutex_unlock(&(phylo->setup->mut_die));
	return (dead);
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
