/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:47:21 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/02 16:53:01 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phylosophers.h"

static int	check_beyond_int(time_t nbr, char n)
{
	if (nbr == LONG_MAX / 10 && n - '0' >= 7)
	{
		printf("Warning: argument went beyond max value.\nMax value is set");
		return (UINT32_MAX);
	}
	return (0);
}

time_t	ft_atol(const char *nptr)
{
	time_t	nbr;

	nbr = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
	{
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (check_beyond_int(nbr, *nptr))
			return (check_beyond_int(nbr, *nptr));
		nbr = nbr * 10 + (time_t)(*nptr - '0');
		nptr++;
	}
	if(*nptr != 0)
		return (0);
	return (nbr);
}

time_t	get_time()
{
	struct timeval	tp;
	time_t			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec * 0.001;
	return (time);
}

time_t	get_timestamp(t_phylos *phylo)
{
	return (get_time() - phylo->setup->start_time);
}

