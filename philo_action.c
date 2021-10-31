#include "philo.h"

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

void	philo_die(t_philo *philo)
{
	put_act(philo, "died");
}

void	philo_think(t_philo *philo)
{
	put_act(philo, "is thinking");
}

