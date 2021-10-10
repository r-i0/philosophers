#include "philo.h"

void	print_help(void)
{
	printf("Usage:\n./philo number_of_philosophers \n\
	time_to_die \n\
	time_to_eat \n\
	time_to_sleep \n\
	[number_of_times_each_philosopher_must_eat]\n");
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
	ft_putnbr_fd(philo->nb, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "is taken a fork");
	pthread_mutex_lock(&(philo->info->fork[philo->right_fork]));
	put_act(philo, "is taken a fork");
	put_act(philo, "is eating");
	sleep(1);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
}

void	*func(void	*philo)
{
	printf("func start\n");
	if (((t_philo*)philo)->nb % 2)
	{
		printf("sleep\n");
		sleep(1);
	}
	while (1)
	{
		philo_eat(philo);
		sleep(1);
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
		print_help();
		return (1);
	}
	if (init_info(argv, &info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	start_dining(&info);
	return (0);
}
