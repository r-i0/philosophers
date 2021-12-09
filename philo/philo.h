/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:36 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/09 09:35:45 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RIGHT 0
# define LEFT 1

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
	int				left_fork;
	int				right_fork;
	int				cnt_eat;
	pthread_t		thread;
	pthread_t		death_thread;
	unsigned long	time_last_eat;
	struct s_rule	*rule;
}	t_philo;

typedef struct s_rule
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
}	t_rule;

// philo_init.c
bool			philo_init(int argc, char **argv, t_rule *rule);

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

// start_dining.c
int				start_dining(t_rule *rule);

// join_threads.c
int				join_threads(t_rule *rule);

// free_rule.c
int				free_rule(t_rule *rule);

// libft
unsigned int	ft_atoui(const char *str, bool *err);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

#endif
