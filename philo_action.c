#include "philo.h"

int	acc_sleep(unsigned long ms)
{
	const unsigned long	time_end = get_ms_timestamp() + ms;
	unsigned long		timestamp;

	timestamp = get_ms_timestamp();
	usleep(ms * 1000 - 1000);
	while (timestamp < time_end)
	{
		usleep(100);
		timestamp = get_ms_timestamp();
		if (timestamp == 0)
			return (-1);
	}
	return (0);
}

unsigned long	put_act(t_philo *philo, char *msg)
{
	const unsigned long	timestamp = get_ms_timestamp();

	pthread_mutex_lock(&(philo->info->mu_end));
	if (philo->info->end == true)
	{
		pthread_mutex_unlock(&(philo->info->mu_end));
		return (0);
	}
	printf("%lu %d %s\n", timestamp, philo->nb, msg);
	pthread_mutex_unlock(&(philo->info->mu_end));
	return (timestamp);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->fork[philo->right_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->mu_time));
	philo->time_last_eat = put_act(philo, "is eating");
	if (philo->time_last_eat == 0)
	{
		pthread_mutex_unlock(&(philo->info->mu_time));
		pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
		pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
		return ;
	}
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->info->mu_time));
	acc_sleep(philo->info->time_sleep);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	const unsigned long	timestamp = put_act(philo, "is sleeping");

	if (timestamp != 0)
	{
		acc_sleep(philo->info->time_sleep);
	}
}

void	philo_die(t_philo *philo)
{
	t_info				*info;
	const unsigned long	timestamp = get_ms_timestamp();

	info = philo->info;
	pthread_mutex_lock(&(info->mu_end));
	if (info->end == false)
	{
		printf("%lu %d died\n", timestamp, philo->nb);
		info->end = true;
	}
	pthread_mutex_unlock(&(info->mu_end));
}

void	philo_think(t_philo *philo)
{
	put_act(philo, "is thinking");
}
