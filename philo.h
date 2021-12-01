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
	int				left_fork;
	int				right_fork;
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	mu_time;
	pthread_mutex_t	mu_end;
	t_philo			*philo;
}	t_info;

int				ft_atoi(const char *str, bool *err);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
bool			philo_init(char **argv, t_info *info);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_die(t_philo *philo);
void			philo_think(t_philo *philo);
void			*observer(void *philo_ptr);

// utils
unsigned long	get_ms_timestamp(void);
int				ft_puterror(char *msg);
int				acc_sleep(unsigned long ms);

#endif
