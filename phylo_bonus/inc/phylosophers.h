/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:52 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/08 16:07:13 by ddavlety         ###   ########.fr       */
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
# include <signal.h>

typedef struct s_phylos
{
	uint32_t		no_phylos;
	time_t			tt_die;
	time_t			tt_eat;
	time_t			tt_sleep;
	time_t			max_eat;
	time_t			start_time;
	uint32_t		no;
	pid_t			pid;
	time_t			eat_time;
	time_t			times_eated;
	sem_t			*forks;
	sem_t			*print;
}					t_phylos;

/*Utils*/
time_t		ft_atol(const char *nptr);
time_t		get_time(void);
time_t		get_timestamp(t_phylos *phylo);

/*Initialization functions*/
t_phylos	*init_info(const char **args);

/*Process functions*/
int			*init_processes(t_phylos *phylo);
int			wait_processes(int *pids, uint32_t phy_no);

/*Rountines functions*/
void		is_eating(t_phylos *phylo);
void		is_sleeping(t_phylos *phylo);
void		is_thinking(t_phylos *phylo);
void		taken_fork(t_phylos *phylo);
void		is_died(t_phylos *phylo);
void		routine_controler(t_phylos *phylo);

/*Mutex functions*/
int			is_dead(t_phylos *phylo);

#endif
