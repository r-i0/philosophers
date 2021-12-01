/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:42 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/01 12:11:43 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*observer(void *philo_ptr)
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
