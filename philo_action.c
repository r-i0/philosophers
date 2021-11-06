/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:28 by rsudo             #+#    #+#             */
/*   Updated: 2021/11/06 10:43:29 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	put_act(t_philo *philo, char *msg)
{
	unsigned long	timestamp;
	bool			end;

	end = false;
	pthread_mutex_lock(&(philo->info->mu_died));
	if (philo->info->end_flag == true)
	{
		end = true;
		timestamp = 0;
	}
	if (end == false)
	{
		timestamp = get_ms_timestamp();
		printf("%lu %d %s\n", timestamp, philo->nb, msg);
	}
	pthread_mutex_unlock(&(philo->info->mu_died));
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
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->info->mu_time));
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	put_act(philo, "is sleeping");
	usleep(philo->info->time_sleep * 1000);
}

void	philo_die(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	put_act(philo, "died");
	pthread_mutex_lock(&(info->mu_died));
	info->end_flag = true;
	pthread_mutex_unlock(&(info->mu_died));
}

void	philo_think(t_philo *philo)
{
	put_act(philo, "is thinking");
}
