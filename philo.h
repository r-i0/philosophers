#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <sys/time.h>

typedef struct s_philo
{
	int			nb;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;
	pthread_t	death_thread;
	unsigned long	time_last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				nb_philo;
	unsigned long	time_die;
	int				time_eat;
	int				time_sleep;
	int				time_must_eat;
	bool			end_flag;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death_check;
	t_philo			*philo;
}	t_info;

int		ft_atoi(const char *str, bool *err);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
bool	philo_init(char **argv, t_info *info);
unsigned long	get_ms_timestamp(void);

#endif
