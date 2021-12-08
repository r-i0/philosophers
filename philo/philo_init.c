/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:12:33 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 11:40:11 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_info *info)
{
	int					i;
	const unsigned long	start_time = get_ms_timestamp();

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&info->mu_fork[i], NULL);
		info->philo[i].nb = i + 1;
		info->philo[i].right_fork = i;
		info->philo[i].left_fork = (i + 1) % info->nb_philo;
		info->philo[i].info = info;
		info->philo[i].time_last_eat = start_time;
		info->philo[i].cnt_eat = 0;
		info->fork[i] = false;
		i++;
	}
}

static bool	is_negative(int argc, t_info *info)
{
	return (info->nb_philo < 1
		|| info->time_die < 1
		|| info->time_eat < 1
		|| info->time_sleep < 1
		|| (argc == 6 && info->times_must_eat < 1));
}

static int	allocate_info(t_info *info)
{
	info->philo = malloc(sizeof(t_philo) * (info->nb_philo));
	if (info->philo == NULL)
		return (-1);
	info->mu_fork = malloc(sizeof(pthread_mutex_t) * (info->nb_philo));
	if (info->mu_fork == NULL)
	{
		free(info->philo);
		return (-1);
	}
	info->fork = malloc(sizeof(bool) * (info->nb_philo));
	if (info->fork == NULL)
	{
		free(info->philo);
		free(info->mu_fork);
		return (-1);
	}
	return (0);
}

static bool	init_info(int argc, char **argv, t_info *info)
{
	bool	err;

	err = false;
	info->times_must_eat = -1;
	info->end = false;
	info->nb_philo = ft_atoui(argv[1], &err);
	info->time_die = (unsigned long)ft_atoui(argv[2], &err);
	info->time_eat = ft_atoui(argv[3], &err);
	info->time_sleep = ft_atoui(argv[4], &err);
	if (argc == 6)
		info->times_must_eat = ft_atoui(argv[5], &err);
	if (err || is_negative(argc, info))
		return (true);
	if (allocate_info(info) == -1)
		return (true);
	if (pthread_mutex_init(&(info->mu_time), NULL))
		return (true);
	if (pthread_mutex_init(&(info->mu_end), NULL))
	{
		pthread_mutex_destroy(&(info->mu_time));
		return (true);
	}
	return (err);
}

bool	philo_init(int argc, char **argv, t_info *info)
{
	bool	err;

	err = init_info(argc, argv, info);
	if (!err)
	{
		init_philo(info);
	}
	return (err);
}
