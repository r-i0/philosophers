#include "philo.h"

int	get_ms_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);//
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&info->fork[i], NULL);
		info->philo[i].nb = i + 1;
		info->philo[i].right_fork = i;
		info->philo[i].left_fork = (i + 1) % info->nb_philo;
		info->philo[i].info = info;
		i++;
	}
}

bool	init_info(char **argv, t_info *info)
{
	bool	err;

	err = false;
	info->time_must_eat = -1;
	info->nb_philo = ft_atoi(argv[1], &err);
	info->time_die = ft_atoi(argv[2], &err);
	info->time_eat = ft_atoi(argv[3], &err);
	info->time_sleep = ft_atoi(argv[4], &err);
	if (argv[5])
		info->time_must_eat = ft_atoi(argv[5], &err);
	info->philo = malloc(sizeof(t_philo) * (info->nb_philo + 1));
	info->fork = malloc(sizeof(pthread_mutex_t) * (info->nb_philo + 1));
	init_philo(info);
	return (err);
}

void	put_act(t_philo *philo, char *msg)
{
	printf("%d %d %s\n", get_ms_timestamp(), philo->nb, msg);
	// ft_putnbr_fd(philo->nb, STDOUT_FILENO);
	// ft_putstr_fd(" ", STDOUT_FILENO);
	// ft_putstr_fd(msg, STDOUT_FILENO);
	// ft_putstr_fd("\n", STDOUT_FILENO);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "is taken a fork");
	pthread_mutex_lock(&(philo->info->fork[philo->right_fork]));
	put_act(philo, "is taken a fork");
	put_act(philo, "is eating");
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
}

void	*func(void	*philo)
{
	printf("func start\n");
	// if (((t_philo*)philo)->nb % 2)
	// {
	// 	printf("sleep\n");
	// 	usleep(50);
	// }
	while (1)
	{
		philo_eat(philo);
		put_act(philo, "is sleeping");
		usleep(((t_philo*)philo)->info->time_sleep * 1000);
		put_act(philo, "is thinking");
	}
	return (NULL);
}

void	start_dining(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_create(&(info->philo[i].thread), NULL, func, &info->philo[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("invalid argument\n", STDERR_FILENO);
		return (1);
	}
	if (init_info(argv, &info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	start_dining(&info);
	int	i = 0;
	while (i < info.nb_philo)
	{
		pthread_join(info.philo[i].thread, NULL);
		i++;
	}
	return (0);
}
