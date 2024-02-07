/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:10 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/07 16:24:23 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

int	check_init(t_setup *s)
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
		return (phylo);
	phylo->forks = sem_open("FORKS", O_CREAT, 0644, (phylo->no_phylos / 2));
	phylo->phylo_dead = sem_open("DEAD", O_CREAT, 0644, 0);
	phylo->phylo_full = sem_open("FULL", O_CREAT, 0644, 0);
	return (phylo);
}

t_phylos	*init_phylo()
{
	t_phylos	*phylo;
	int32_t		status;


	phylo = (t_phylos *)malloc(sizeof(t_phylos));
	if (!phylo)
		return (NULL); // del
	if (phylo->pid == 0)
		init_process(phylo);
	else
		free(phylo);
	return (NULL); // ??
}

t_phylos	**init_phylos(t_setup *setup)
{
	uint32_t	i;
	t_phylos	*phylos[setup->no_phylos + 1];


	i = 0;
	phylos[setup->no_phylos] = NULL;
	while (i < setup->no_phylos)
	{
		phylos[i] = init_phylo(setup, (i + 1));
		i++;
	}
	return (phylos); // ??
}

