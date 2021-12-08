/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:36 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 11:18:24 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <assert.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb;
	int				left_mu_fork;
	int				right_mu_fork;
	int				cnt_eat;
	pthread_t		thread;
	pthread_t		death_thread;
	unsigned long	time_last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				nb_philo;
	unsigned long	time_die;
	int				time_eat;
	int				time_sleep;
	int				times_must_eat;
	bool			end;
	bool			*fork;
	pthread_mutex_t	*mu_fork;
	pthread_mutex_t	mu_time;
	pthread_mutex_t	mu_end;
	t_philo			*philo;
}	t_info;

// philo_init.c
bool			philo_init(int argc, char **argv, t_info *info);

// philo_action.c
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_die(t_philo *philo);
void			philo_think(t_philo *philo);
unsigned long	put_act(t_philo *philo, char *msg);

// observer.c
void			*observer(void *philo_ptr);

// utils.c
unsigned long	get_ms_timestamp(void);
int				ft_puterror(char *msg);
int				acc_sleep(unsigned long ms);

// philo_routine.c
void			*philo_routine(void *philo_ptr);

int	start_dining(t_info *info);

// join_threads.c
int				join_threads(t_info *info);

// free_info.c
int				free_info(t_info *info);

// libft
unsigned int	ft_atoui(const char *str, bool *err);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

#endif
