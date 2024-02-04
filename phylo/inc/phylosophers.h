/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:52 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/04 18:00:20 by ddavlety         ###   ########.fr       */
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
# include <string.h>
# include <stdint.h>

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
	bool			phylo_dead;
	bool			phylo_full;
	pthread_mutex_t	mut_die;
}					t_setup;

typedef struct s_phylos
{
	uint32_t		no;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	time_t			eat_time;
	time_t			times_eated;
	pthread_mutex_t	mut_eat;
	struct s_setup	*setup;
}					t_phylos;

/*Utils*/
time_t		ft_atol(const char *nptr);
time_t		get_time(void);
time_t		get_timestamp(t_phylos *phylo);
int			try_fork_first(t_phylos *phylo);
int			try_fork(t_phylos *phylo);
void		*check_die(void *ptr);
int			usage_message(void);
int			error_message(void);

/*Initialization functions*/
t_setup		*init_info(const char **args);
t_phylos	**init_phylos(t_setup *setup);
t_phylos	*init_phylo(t_setup *setup, uint32_t no, t_phylos **phylos);

/*Thread functions*/
int			init_thread(t_phylos **phylos);
int			join_threads(t_phylos **phylos);

/*Rountines functions*/
void		is_eating(t_phylos *phylo);
void		is_sleeping(t_phylos *phylo);
void		is_thinking(t_phylos *phylo);
void		taken_fork(t_phylos *phylo);
void		is_died(t_phylos *phylo);
void		*routine_controler(void *ptr);
int			check_dead(t_phylos *phylo);

/*Termination functions*/
int			terminate_phylos(t_phylos **phylos, int code);
int			terminate_setup(t_setup **setup_ptr, int code);

#endif
