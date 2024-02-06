/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:52 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/06 14:11:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYLOSOPHERS_H
# define PHYLOSOPHERS_H

/*Includes*/
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SEMA_NAME "phylo_bonus"

/*Type definitions*/
typedef struct s_setup
{
	uint32_t		no_phylos;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	time_t			max_eat;
	time_t			start_time;
	pid_t			child;
	bool			phylo_dead;
	bool			phylo_full;
}					t_setup;

typedef struct s_phylos
{
	uint32_t		no;
	pid_t			pid;
	time_t			eat_time;
	time_t			times_eated;
	sem_t			*sem;
	struct s_setup	*setup;
}					t_phylos;

/*Utils*/
time_t		ft_atol(const char *nptr);
time_t		get_time(void);
time_t		get_timestamp(t_phylos *phylo);
int			try_fork_first(t_phylos *phylo);
int			try_fork(t_phylos *phylo);
void		check_die(t_phylos **phylo);

/*Initialization functions*/
t_setup		*init_info(const char **args);
t_phylos	**init_phylos(t_setup *setup);
t_phylos	*init_phylo(t_setup *setup, uint32_t no);
/*Process functions*/
int			init_process(t_phylos **phylos);
int			wait_process(t_phylos **phylos);

/*Rountines functions*/
void		is_eating(t_phylos *phylo);
void		is_sleeping(t_phylos *phylo);
void		is_thinking(t_phylos *phylo);
void		taken_fork(t_phylos *phylo);
void		is_died(uint32_t j, t_phylos **phylos);
void		*routine_controler(t_phylos *phylo);
/*Mutex functions*/
int			check_dead(t_phylos *phylo);

#endif
