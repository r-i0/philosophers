#include "philo.h"

bool	is_all_philos_ate(t_info *info)
{
	int		i;
	bool	ate;

	i = 0;
	ate = false;
	pthread_mutex_lock(&(info->mu_time));
	while (info->times_must_eat != -1 && i < info->nb_philo)
	{
		if (info->philo[i].cnt_eat < info->times_must_eat)
			ate = true;
		i++;
	}
	pthread_mutex_unlock(&(info->mu_time));
	return (ate);
}

unsigned long	get_ms_timestamp(void)
{
	struct timeval	tv;
	int				ret;

	ret = gettimeofday(&tv, NULL);
	if (ret == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return (0);
}

void	*philo_routine(void *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;

	philo = philo_ptr;
	info = philo->info;
	if (philo->nb % 2)
	{
		usleep(500);
	}
	while (1)
	{
		pthread_mutex_lock(&(info->mu_died));
		if (info->end_flag == true)
		{
			pthread_mutex_unlock(&(info->mu_died));
			break ;
		}
		pthread_mutex_unlock(&(info->mu_died));
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

bool	is_end(t_info *info)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&(info->mu_died));
	if (info->end_flag == true)
	{
		end = true;
	}
	pthread_mutex_unlock(&(info->mu_died));
	return (end);
}

bool	is_die(t_info *info, t_philo *philo)
{
	bool	die;

	die = false;
	pthread_mutex_lock(&(info->mu_time));
	if (get_ms_timestamp() - philo->time_last_eat > info->time_die)
	{
		die = true;
	}
	pthread_mutex_unlock(&(info->mu_time));
	return (die);
}

void	*observe_philo_dead(void *philo_ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = philo_ptr;
	info = philo->info;
	while (1)
	{
		if (is_end(info))
			break ;
		if (is_all_philos_ate(info))
		{
			pthread_mutex_lock(&(info->mu_died));
			info->end_flag = true;
			pthread_mutex_unlock(&(info->mu_died));
			break ;
		}
		if (is_die(info, philo))
		{
			philo_die(philo);
			break ;
		}
	}
	return (NULL);
}

int	start_dining(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
			return (-1);
		if (pthread_create(&philo[i].death_thread, NULL, observe_philo_dead, &philo[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			return (-1);
		if (pthread_join(info->philo[i].death_thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
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
	if (start_dining(&info) == -1)
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	if (join_thread(&info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
