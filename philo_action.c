/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:28 by rsudo             #+#    #+#             */
/*   Updated: 2021/11/25 11:07:25 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	put_act(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&(philo->info->mu_died));
	if (philo->info->end_flag == true)
	{
		timestamp = 0;
	}
	else
	{
		timestamp = get_ms_timestamp();
		printf("%lu %d %s\n", timestamp, philo->nb, msg);
	}
	pthread_mutex_unlock(&(philo->info->mu_died));
	return (timestamp);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->fork[philo->right_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->info->mu_time));
	philo->time_last_eat = put_act(philo, "is eating");
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->info->mu_time));
	divide_sleep(philo->info->time_eat);
	pthread_mutex_unlock(&(philo->info->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right_fork]));
	return (1);
}

void divide_sleep(unsigned long ms)
{
	unsigned long time_end = get_ms_timestamp() + ms;
	unsigned long time_left = time_end - get_ms_timestamp();
	while (time_left / 2 > 10)
	{
		usleep((time_left / 2) * 1000);
		time_left = time_end - get_ms_timestamp();
	}
	while (time_left != 0)
	{
		usleep(10);
		time_left = time_end - get_ms_timestamp();
	}
}

void	philo_sleep(t_philo *philo)
{
	put_act(philo, "is sleeping");
	divide_sleep(philo->info->time_sleep);
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
