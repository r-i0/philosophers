/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:43:43 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 11:00:00 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_one_philo(t_info *info)
{
	pthread_mutex_lock(&info->mu_time);
	if (info->nb_philo == 1)
	{
		pthread_mutex_unlock(&info->mu_time);
		return (true);
	}
	pthread_mutex_unlock(&info->mu_time);
	return (false);
}

static void	*one_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->mu_fork[philo->left_mu_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_unlock(&(info->mu_fork[philo->left_mu_fork]));
	while (1)
	{
		pthread_mutex_lock(&(info->mu_end));
		if (info->end == true)
		{
			pthread_mutex_unlock(&(info->mu_end));
			break ;
		}
		pthread_mutex_unlock(&(info->mu_end));
	}
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;

	philo = philo_ptr;
	info = philo->info;
	if (is_one_philo(info))
		return (one_philo(info, philo));
	if (philo->nb % 2)
		usleep(1000);
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
