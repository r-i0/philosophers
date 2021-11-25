/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:40:17 by rsudo             #+#    #+#             */
/*   Updated: 2021/11/25 15:47:44 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_all_philos_ate(t_info *info)
{
	int		i;
	bool	ate;

	i = 0;
	ate = true;
	pthread_mutex_lock(&(info->mu_time));
	while (info->times_must_eat != -1 && i < info->nb_philo)
	{
		if (info->philo[i].cnt_eat < info->times_must_eat)
			ate = false;
		i++;
	}
	if (info->times_must_eat == -1)
		ate = false;
	pthread_mutex_unlock(&(info->mu_time));
	return (ate);
}

unsigned long	get_ms_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	philo_eat_one(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	return (1);
}

void	*philo_routine(void *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;
	int one;

	one = 0;
	philo = philo_ptr;
	info = philo->info;
	if (philo->nb % 2)
	{
		usleep(100);
	}
	pthread_mutex_lock(&info->mu_time);
	if (info->nb_philo == 1)
		one = philo_eat_one(philo);
	pthread_mutex_unlock(&info->mu_time);
	while (1)
	{
		pthread_mutex_lock(&(info->mu_died));
		if (info->end_flag == true)
		{
			pthread_mutex_unlock(&(info->mu_died));
			break ;
		}
		pthread_mutex_unlock(&(info->mu_died));
		if (one == 0)
		{
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
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

void	*observe_philo_end(void *philo_ptr)
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

void	start_dining(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		pthread_create(&philo[i].death_thread, NULL, \
				observe_philo_end, &philo[i]);
		i++;
	}
}

void	join_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		pthread_join(info->philo[i].death_thread, NULL);
		i++;
	}
}

void	free_and_destoroy(t_info *info)
{
	free(info->philo);
	free(info->fork);
	pthread_mutex_destroy(&(info->mu_time));
	pthread_mutex_destroy(&(info->mu_died));
}

void end(void)__attribute__((destructor));

void end(void)
{
    system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
	{
		/* divide_sleep(20000); */
		ft_putstr_fd("invalid argument\n", STDERR_FILENO);
		return (1);
	}
	if (philo_init(argv, &info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	start_dining(&info);
	join_thread(&info);
	free_and_destoroy(&info);
	return (0);
}
