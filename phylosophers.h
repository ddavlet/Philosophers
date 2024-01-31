/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:52 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/31 14:19:56 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYLOSOPHERS_H
# define PHYLOSOPHERS_H

/*Includes*/
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

/*Type definitions*/


typedef struct s_setup
{
	uint32_t		no_phylos;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	time_t			max_eat;
	pthread_mutex_t	print;
	time_t			start_time;
	pthread_t		th_die;
}					t_setup;

typedef struct s_phylos
{
	uint32_t		no;
	bool			dead;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	time_t			tt_die;
	time_t			eat_time;
	time_t			times_eated;
	pthread_mutex_t	mut_eat;
	struct s_setup	*setup;
}					t_phylos;


time_t		ft_atol(const char *nptr);
time_t		get_time();
time_t		get_timestamp(t_phylos *phylo);

/*Initialization functions*/
t_setup		*init_info(const char **args);
t_phylos	**init_phylos(t_setup *setup);
t_phylos	*init_phylo(t_setup *setup, uint32_t no, t_phylos **phylos);

/*Thread functions*/
int			init_thread(t_phylos **phylos);

/*Rountines functions*/
void		is_eating(t_phylos *phylo);
void		is_sleeping(t_phylos *phylo);
void		is_thinking(t_phylos *phylo);
void		taken_fork(t_phylos *phylo);

/*!!!temporary!!!*/
void		*some_fucntion(void *ptr);
void		debug_print(t_phylos *phylo, const char *txt);

#endif
