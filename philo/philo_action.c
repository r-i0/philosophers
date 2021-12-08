/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:40 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 10:16:05 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	put_act(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&(philo->info->mu_end));
	if (philo->info->end == true)
	{
		pthread_mutex_unlock(&(philo->info->mu_end));
		return (0);
	}
	timestamp = get_ms_timestamp();
	printf("%lu %d %s\n", timestamp, philo->nb, msg);
	pthread_mutex_unlock(&(philo->info->mu_end));
	return (timestamp);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->mu_fork[philo->left_mu_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->mu_fork[philo->right_mu_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->mu_time));
	philo->time_last_eat = put_act(philo, "is eating");
	if (philo->time_last_eat == 0)
	{
		pthread_mutex_unlock(&(philo->info->mu_time));
		pthread_mutex_unlock(&(philo->info->mu_fork[philo->left_mu_fork]));
		pthread_mutex_unlock(&(philo->info->mu_fork[philo->right_mu_fork]));
		return ;
	}
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->info->mu_time));
	acc_sleep(philo->info->time_sleep);
	pthread_mutex_unlock(&(philo->info->mu_fork[philo->left_mu_fork]));
	pthread_mutex_unlock(&(philo->info->mu_fork[philo->right_mu_fork]));
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
