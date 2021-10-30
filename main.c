#include "philo.h"
#include <pthread.h>
#include <stdio.h>

unsigned long	get_ms_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);//
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	put_act(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	if (philo->info->end_flag == true)
		return (0);
	timestamp = get_ms_timestamp();
	printf("%lu %d %s\n", timestamp, philo->nb, msg);
	return (timestamp);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->fork[philo->right_fork]));
	put_act(philo, "has taken a fork");
	philo->time_last_eat = put_act(philo, "is eating");
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	put_act(philo, "is sleeping");
	usleep(((t_philo*)philo)->info->time_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	put_act(philo, "is thinking");
}

void	*philo_routine(void *philo)
{
	t_info	*info;

	info = ((t_philo*)philo)->info;
	if (((t_philo*)philo)->nb % 2)
	{
		usleep(100);
	}
	while (1)
	{
		if (info->end_flag == true)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	philo_die(t_philo *philo)
{
	put_act(philo, "died");
}

void	*observe_philo_dead(void *philo_ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = philo_ptr;
	info = philo->info;
	while (philo->info->end_flag == false)
	{
		if (get_ms_timestamp() - philo->time_last_eat > philo->info->time_die)
		{
			philo_die(philo);
			info->end_flag = true;
		}
	}
	return (NULL);
}

void	start_dining(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_create(&(info->philo[i].thread), NULL, philo_routine, &info->philo[i]);
		pthread_create(&(info->philo[i].death_thread), NULL, observe_philo_dead, &info->philo[i]);
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
	if (philo_init(argv, &info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	start_dining(&info);
	int	i = 0;
	while (i < info.nb_philo)
	{
		pthread_join(info.philo[i].thread, NULL);
		pthread_join(info.philo[i].death_thread, NULL);
		i++;
	}
	return (0);
}
