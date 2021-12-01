#include "philo.h"

bool	is_all_philos_ate(t_info *info)
{
	int		i;
	bool	ate;

	i = 0;
	ate = true;
	pthread_mutex_lock(&(info->mu_time));
	if (info->times_must_eat == -1)
	{
		pthread_mutex_unlock(&(info->mu_time));
		return (false);
	}
	while (i < info->nb_philo)
	{
		if (info->philo[i].cnt_eat < info->times_must_eat)
			ate = false;
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
	if (ret != 0)
	{
		ft_putstr_fd("error: gettimeofday\n", STDERR_FILENO);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
		pthread_mutex_lock(&(info->mu_end));
		if (info->end == true)
		{
			pthread_mutex_unlock(&(info->mu_end));
			break ;
		}
		pthread_mutex_unlock(&(info->mu_end));
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
	pthread_mutex_lock(&(info->mu_end));
	if (info->end == true)
	{
		end = true;
	}
	pthread_mutex_unlock(&(info->mu_end));
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
			pthread_mutex_lock(&(info->mu_end));
			info->end = true;
			pthread_mutex_unlock(&(info->mu_end));
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

int	free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&(info->fork[i])) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&(info->mu_time)))
		return (-1);
	if (pthread_mutex_destroy(&(info->mu_end)))
		return (-1);
	free(info->philo);
	free(info->fork);
	return (0);
}

/* void end(void)__attribute__((destructor)); */

/* void end(void) */
/* { */
/*     system("leaks philo"); */
/* } */

int	ft_puterror(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_puterror("invalid argument\n"));
	if (philo_init(argv, &info))
		return (ft_puterror("error: init\n"));
	if (start_dining(&info) == -1)
		return (ft_puterror("error: pthread_create\n"));
	if (join_thread(&info))
		return (ft_puterror("error: pthread_join\n"));
	if (free_info(&info))
		return (ft_puterror("error: pthread_destroy\n"));
	return (0);
}
