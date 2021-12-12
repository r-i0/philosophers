/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:45:32 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/12 23:45:33 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->rule->mu_fork[philo->left_fork]));
	philo->rule->fork[philo->left_fork] = true;
	put_act(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->rule->mu_fork[philo->right_fork]));
	philo->rule->fork[philo->right_fork] = true;
	put_act(philo, "has taken a fork");
}

static void	drop_fork(t_philo *philo)
{
	philo->rule->fork[philo->left_fork] = false;
	pthread_mutex_unlock(&(philo->rule->mu_fork[philo->left_fork]));
	philo->rule->fork[philo->right_fork] = false;
	pthread_mutex_unlock(&(philo->rule->mu_fork[philo->right_fork]));
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&(philo->rule->mu_time));
	philo->time_last_eat = put_act(philo, "is eating");
	if (philo->time_last_eat == 0)
	{
		pthread_mutex_unlock(&(philo->rule->mu_time));
		drop_fork(philo);
		return ;
	}
	philo->cnt_eat++;
	pthread_mutex_unlock(&(philo->rule->mu_time));
	acc_sleep(philo->rule->time_eat);
	drop_fork(philo);
}
