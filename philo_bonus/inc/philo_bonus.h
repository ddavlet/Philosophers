/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:47:52 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 13:50:58 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

typedef struct s_philos
{
	uint32_t		no_philos;
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
	pt
}					t_philos;

/*Utils*/
time_t		ft_atol(const char *nptr);
time_t		get_time(void);
time_t		get_timestamp(t_philos *philo);
void		destroy_semaph(t_philos *philo);

/*Initialization functions*/
t_philos	*init_info(const char **args);

/*Process functions*/
int			*init_processes(t_philos *philo);
int			wait_processes(int *pids, uint32_t phy_no);

/*Rountines functions*/
void		is_eating(t_philos *philo);
void		is_sleeping(t_philos *philo);
void		is_thinking(t_philos *philo);
void		taken_fork(t_philos *philo);
void		is_died(t_philos *philo);
void		routine_controler(t_philos *philo);

/*Mutex functions*/
void		is_dead(t_philos *philo);

#endif
