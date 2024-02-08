/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:10 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:03:57 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	check_init(t_phylos *s)
{
	if (!s->no_phylos
		|| !s->tt_die
		|| !s->tt_eat
		|| !s->tt_sleep
		|| !s->max_eat)
		return (1);
	return (0);
}

t_phylos	*init_info(const char **args)
{
	t_phylos	*phylo;

	phylo = (t_phylos *)malloc(sizeof(t_phylos));
	phylo->start_time = get_time();
	phylo->no_phylos = ft_atol(args[0]);
	phylo->tt_die = ft_atol(args[1]);
	phylo->tt_eat = ft_atol(args[2]);
	phylo->tt_sleep = ft_atol(args[3]);
	phylo->eat_time = get_time();
	phylo->times_eated = 0;
	if (args[4])
		phylo->max_eat = ft_atol(args[4]);
	else
		phylo->max_eat = UINT32_MAX;
	if (check_init(phylo))
	{
		free(phylo);
		return (NULL);
	}
	phylo->forks = sem_open("/FORKS", O_CREAT, 0644, phylo->no_phylos / 2);
	phylo->print = sem_open("/PRINT", O_CREAT, 0644, 1);
	return (phylo);
}
