#include "philo.h"

static void	init_philo(t_info *info)
{
	int					i;
	const unsigned long	start_time = get_ms_timestamp();

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&info->fork[i], NULL);
		info->philo[i].nb = i + 1;
		info->philo[i].right_fork = i;
		info->philo[i].left_fork = (i + 1) % info->nb_philo;
		info->philo[i].info = info;
		info->philo[i].time_last_eat = start_time;
		info->philo[i].cnt_eat = 0;
		i++;
	}
}

static bool	init_info(char **argv, t_info *info)
{
	bool	err;

	err = false;
	info->times_must_eat = -1;
	info->end = false;
	info->nb_philo = ft_atoi(argv[1], &err);
	info->time_die = (unsigned long)ft_atoi(argv[2], &err);
	info->time_eat = ft_atoi(argv[3], &err);
	info->time_sleep = ft_atoi(argv[4], &err);
	if (argv[5])
		info->times_must_eat = ft_atoi(argv[5], &err);
	info->philo = malloc(sizeof(t_philo) * (info->nb_philo + 1));
	info->fork = malloc(sizeof(pthread_mutex_t) * (info->nb_philo + 1));
	if (info->philo == NULL || info->fork == NULL)
		err = true;
	pthread_mutex_init(&(info->mu_time), NULL);
	pthread_mutex_init(&(info->mu_end), NULL);
	return (err);
}

bool	philo_init(char **argv, t_info *info)
{
	bool	err;

	err = init_info(argv, info);
	init_philo(info);
	return (err);
}
