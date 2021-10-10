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

typedef struct s_philo
{
	int			nb;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_must_eat;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_info;

int		ft_atoi(const char *str, bool *err);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
