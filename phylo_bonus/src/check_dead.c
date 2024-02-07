/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:56:12 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/06 16:28:12 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	is_dead(t_phylos *phylo)
{
	int	time;

	time = phylo->setup->tt_die  - (get_time() - phylo->eat_time);
	if (time <= 0)
		return (1);
	else
		return (0);
}

uint32_t	times_eated(t_phylos *phylos)
{
	uint32_t	i;

	i = phylos->times_eated;
	return (i);
}

int	check_dead(t_phylos *phylo)
{
	bool dead;

	dead = phylo->setup->phylo_dead;
	return (dead);
}

/*Multiplication may overflow*/
void	check_die(t_phylos	**phylos)
{
	uint32_t	i;
	uint32_t	t;

	while (1)
	{
		i = 0;
		t = 0;
		while (phylos[i])
		{
			if (is_dead(phylos[i]))
				exit(i);
			t += phylos[i]->times_eated;
			if (t == 0 && i == (phylos[i]->setup->no_phylos - 1))
				exit(2);
			i++;
		}
	}
}
