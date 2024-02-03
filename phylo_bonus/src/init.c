/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:10 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 06:57:30 by ddavlety         ###   ########.fr       */
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

t_setup	*init_info(const char **args)
{
	t_setup	*setup;

	setup = (t_setup *)malloc(sizeof(t_setup));
	setup->start_time = get_time();
	setup->phylo_dead = false;
	setup->no_phylos = ft_atol(args[0]);
	setup->tt_die = ft_atol(args[1]);
	setup->tt_eat = ft_atol(args[2]);
	setup->tt_sleep = ft_atol(args[3]);
	if (args[4])
		setup->max_eat = ft_atol(args[4]);
	else
		setup->max_eat = UINT32_MAX;
	if (check_init(setup))
		return (setup); // dela
	return(setup);
}

t_phylos	*init_phylo(t_setup *setup, uint32_t no)
{
	t_phylos	*new_phylo;

	new_phylo = (t_phylos *)malloc(sizeof(t_phylos));
	if (!new_phylo)
		return (NULL); // dela
	new_phylo->no = no;
	new_phylo->eat_time = get_time();
	new_phylo->times_eated = 0;
	new_phylo->setup = setup;
	new_phylo->pid = fork();
	if (new_phylo->pid < 0)
		return (new_phylo);
	return (new_phylo);
}

t_phylos	**init_phylos(t_setup *setup)
{
	uint32_t	i;
	t_phylos	**phylosofers;

	i = 0;
	phylosofers = (t_phylos **)malloc(sizeof(t_phylos *) * (setup->no_phylos + 1));
	if (!phylosofers)
		return (NULL); //dela
	phylosofers[setup->no_phylos] = 0;
	while (i < setup->no_phylos)
	{
		phylosofers[i] = init_phylo(setup, (i + 1));
		i++;
	}
	return (phylosofers);
}

