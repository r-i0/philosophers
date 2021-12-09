/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:40 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/09 09:37:18 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo, int side)
{
	if (side == RIGHT)
	{
		pthread_mutex_lock(&(philo->rule->mu_fork[philo->right_fork]));
		philo->rule->fork[philo->right_fork] = true;
		put_act(philo, "has taken a fork");
	}
	if (side == LEFT)
	{
		pthread_mutex_lock(&(philo->rule->mu_fork[philo->left_fork]));
		philo->rule->fork[philo->left_fork] = true;
		put_act(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo, LEFT);
	take_fork(philo, RIGHT);
	pthread_mutex_lock(&(philo->rule->mu_time));
	philo->time_last_eat = put_act(philo, "is eating");
	if (philo->time_last_eat == 0)
	{
		pthread_mutex_unlock(&(philo->rule->mu_time));
		philo->rule->fork[philo->left_fork] = false;
		pthread_mutex_unlock(&(philo->rule->mu_fork[philo->left_fork]));
		philo->rule->fork[philo->right_fork] = false;
		pthread_mutex_unlock(&(philo->rule->mu_fork[philo->right_fork]));
		return ;
	}
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->rule->mu_time));
	acc_sleep(philo->rule->time_sleep);
	philo->rule->fork[philo->left_fork] = false;
	pthread_mutex_unlock(&(philo->rule->mu_fork[philo->left_fork]));
	philo->rule->fork[philo->right_fork] = false;
	pthread_mutex_unlock(&(philo->rule->mu_fork[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	const unsigned long	timestamp = put_act(philo, "is sleeping");

	if (timestamp != 0)
	{
		acc_sleep(philo->rule->time_sleep);
	}
}

void	philo_die(t_philo *philo)
{
	t_rule				*rule;
	const unsigned long	timestamp = get_ms_timestamp();

	rule = philo->rule;
	pthread_mutex_lock(&(rule->mu_end));
	if (rule->end == false)
	{
		printf("%lu %d died\n", timestamp, philo->nb);
		rule->end = true;
	}
	pthread_mutex_unlock(&(rule->mu_end));
}

void	philo_think(t_philo *philo)
{
	put_act(philo, "is thinking");
}
